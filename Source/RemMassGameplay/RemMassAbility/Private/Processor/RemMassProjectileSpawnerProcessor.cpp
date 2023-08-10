// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassProjectileSpawnerProcessor.h"

#include "GameplayTagContainer.h"
#include "MassCommonFragments.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassAbilityTags.h"
#include "RemMassProcessorGroupNames.h"
#include "RemMassSpawner.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "SpawnDataGenerator/RemMassProjectileRegenerator.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

URemMassProjectileSpawnerProcessor::URemMassProjectileSpawnerProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::SpawnProjectile;
	ExecutionOrder.ExecuteBefore.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassProjectileSpawnerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassProjectileSpawnerFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassOwnerFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassProjectileNextSpawnTimeFragment>(EMassFragmentAccess::ReadWrite);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadOnly);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassProjectileSpawnerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassProjectileSpawnerProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& GameStateSubsystem = Context.GetSubsystemChecked<URemMassGameStateSubsystem>();
		
		const auto NumEntities = Context.GetNumEntities();
		const auto TimeSeconds = GameStateSubsystem.GetWorld()->GetTimeSeconds();

		const auto SpawnerView = Context.GetFragmentView<FRemMassProjectileSpawnerFragment>();
		const auto OwnerView = Context.GetFragmentView<FRemMassOwnerFragment>();
		const auto NextSpawnTimeView = Context.GetMutableFragmentView<FRemMassProjectileNextSpawnTimeFragment>();

		auto* ProjectileSpawner = GameStateSubsystem.GetMassSpawner(FGameplayTagQuery::MakeQuery_MatchAnyTags(
				Rem::Common::GetDefaultRef<URemMassAbilityTags>().GetProjectileMassSpawnerTag().GetSingleTagContainer()));

		RemCheckVariable(ProjectileSpawner, return;, REM_NO_LOG_BUT_ENSURE);

		auto* EntityRegenerator = ProjectileSpawner->GetSpawnDataGenerator<URemMassProjectileRegenerator>();
		RemCheckVariable(EntityRegenerator, return;, REM_NO_LOG_BUT_ENSURE);
		
		FRemProjectileSpawnDataContainer SpawnDataContainer;
		SpawnDataContainer.Reserve(NumEntities);

		TMap<FMassEntityHandle, FRemMassNearbyMonsterEntityData> NearbyMonsterEntityDataMap;
		for (int32 Index = 0; Index < NumEntities; ++Index)
		{
			const auto PlayerEntityHandle = OwnerView[Index].Value;
			RemCheckVariable(PlayerEntityHandle, continue;, REM_NO_LOG_BUT_ENSURE);

			const FRemMassNearbyMonsterEntityData* NearbyMonsterEntityData;
			if (NearbyMonsterEntityData = NearbyMonsterEntityDataMap.Find(PlayerEntityHandle);
				!NearbyMonsterEntityData)
			{
				NearbyMonsterEntityData = &NearbyMonsterEntityDataMap.Add(PlayerEntityHandle,
					GameStateSubsystem.GetNearbyMonsterEntityData(PlayerEntityHandle));
			}

			RemCheckVariable(NearbyMonsterEntityData, continue;, REM_NO_LOG_BUT_ENSURE);
			
			if (const auto NextSpawnTime = NextSpawnTimeView[Index];
				TimeSeconds < NextSpawnTime.Value)
			{
				continue;
			}

			NextSpawnTimeView[Index].Value = TimeSeconds + SpawnerView[Index].SpawnInterval;

			const auto ConfigAsset = SpawnerView[Index].ProjectileConfigAsset;
			RemCheckVariable(ConfigAsset, return;, REM_NO_LOG_BUT_ENSURE);
			
			const auto Owner = FMassEntityView{Context.GetEntityManagerChecked(), PlayerEntityHandle};
			const auto& OwnerTransform = Owner.GetFragmentData<FTransformFragment>();

			const int32 ContainerIndex = SpawnDataContainer.FindOrAdd(ConfigAsset);
			auto& [Locations, Rotations, InitialVelocities]
				= SpawnDataContainer.SpawnData[ContainerIndex];
			
			Locations.Add(OwnerTransform.GetTransform().GetLocation());
			
			const auto RotationQuat = OwnerTransform.GetTransform().GetRotation();
			Rotations.Add(RotationQuat);

			const auto Velocity = SpawnerView[Index].InitialSpeed * (NearbyMonsterEntityData->NearbyMonsterDirections.IsEmpty()
				                      ? RotationQuat.GetForwardVector()
				                      : NearbyMonsterEntityData->NearbyMonsterDirections[0]);
			
			InitialVelocities.Add(Velocity);
		}

		if (SpawnDataContainer.ConfigAssets.Num() > 0)
		{
			EntityRegenerator->AddSpawnData(std::move(SpawnDataContainer));

			Context.Defer().PushCommand<FMassDeferredCreateCommand>([WeakRegenerator = TWeakObjectPtr<URemMassProjectileRegenerator>{EntityRegenerator}]
				(FMassEntityManager&)
			{
				if (WeakRegenerator.IsValid())
				{
					Rem::Mass::FScopedEntitySpawnDataRegeneration SpawnDataRegeneration{*WeakRegenerator.Get()};
				}
			});
		}
	});
}
