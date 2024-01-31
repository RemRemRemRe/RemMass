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
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::SpawnProjectile;
	ExecutionOrder.ExecuteBefore.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassProjectileSpawnerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassProjectileConfigAssetFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassProjectileInfoFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassProjectileTriggerInfoFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassProjectileTriggerStateFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FRemMassOwnerFragment>(EMassFragmentAccess::ReadOnly);

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

		const auto ConfigAssetView = Context.GetFragmentView<FRemMassProjectileConfigAssetFragment>();
		const auto ProjectileInfoView = Context.GetFragmentView<FRemMassProjectileInfoFragment>();
		const auto TriggerInfoView = Context.GetFragmentView<FRemMassProjectileTriggerInfoFragment>();
		const auto TriggerStateView = Context.GetMutableFragmentView<FRemMassProjectileTriggerStateFragment>();
		const auto OwnerView = Context.GetFragmentView<FRemMassOwnerFragment>();

		auto* ProjectileSpawner = GameStateSubsystem.GetMassSpawner(FGameplayTagQuery::MakeQuery_MatchAnyTags(
				Rem::GetDefaultRef<URemMassAbilityTags>().GetProjectileMassSpawnerTag().GetSingleTagContainer()));

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

			auto& TriggerInfo = TriggerInfoView[Index];
			auto& TriggerState = TriggerStateView[Index];

			auto CanTrigger = [](const FRemMassProjectileTriggerInfoFragment& Info, const FRemMassProjectileTriggerStateFragment& State, const double Time)
			{
				// only one round, or max round reached
				if ((Info.RoundsPerInterval <= 1 || Info.RoundsPerInterval == State.CurrentRounds) && (Info.ShotsPerRound <= 1 || Info.ShotsPerRound == State.CurrentShots))
				{
					return Time > State.NextTriggeringTime;
				}

				return Time > State.NextShotTime;
			};

			auto IncrementShotCount = [](const FRemMassProjectileTriggerInfoFragment& Info, FRemMassProjectileTriggerStateFragment& State, const double Time)
			{
				if (const auto NewShotCount = ++State.CurrentShots;
					NewShotCount == Info.ShotsPerRound)
				{
					State.CurrentShots = 0;
					
					++State.CurrentRounds;
					if (State.CurrentRounds == Info.RoundsPerInterval)
					{
						// clear state
						State.NextShotTime = 0.0f;	
					}
					else
					{
						State.NextShotTime = Time + Info.RoundsInterval;
					}
				}
				else
				{
					State.CurrentShots = NewShotCount;
					State.NextShotTime = Time + Info.ShotsInterval;
				}
			};
			
			if (TimeSeconds > TriggerState.NextTriggeringTime)
			{
				TriggerState = {};
				TriggerState.NextTriggeringTime = TimeSeconds + TriggerInfo.TriggerInterval;
			}
			
			if (!CanTrigger(TriggerInfo, TriggerState, TimeSeconds))
			{
				continue;
			}

			const auto ConfigAsset = ConfigAssetView[Index].ProjectileConfigAsset;
			RemCheckVariable(ConfigAsset, return;, REM_NO_LOG_BUT_ENSURE);
			
			const auto Owner = FMassEntityView{Context.GetEntityManagerChecked(), PlayerEntityHandle};
			const auto& OwnerTransform = Owner.GetFragmentData<FTransformFragment>().GetTransform();

			const int32 ContainerIndex = SpawnDataContainer.FindOrAdd(ConfigAsset);
			auto& [Locations, Rotations, InitialVelocities]
				= SpawnDataContainer.SpawnData[ContainerIndex];

			const uint8 LoopCount = TriggerInfo.ShotsInterval > 0 ? 1: TriggerInfo.ShotsPerRound;
			
			constexpr float Degree = 180.0f;
			const float AverageDegree = Degree / (TriggerInfo.ShotsPerRound + 1);

			const auto& OwnerLocation = OwnerTransform.GetLocation();
			const auto& OwnerRotation = OwnerTransform.GetRotation();
			const auto& ProjectileDirection = NearbyMonsterEntityData->NearbyMonsterDirections.IsEmpty()
										  ? OwnerRotation
										  : NearbyMonsterEntityData->NearbyMonsterDirections[0].Rotation().Quaternion();
			for (uint8 Counter = 0; Counter < LoopCount; ++Counter)
			{
				IncrementShotCount(TriggerInfo, TriggerState, TimeSeconds);
				
				Locations.Add(OwnerLocation);
				{
					const float AngleToRotate = TriggerState.CurrentShots * AverageDegree;

					const FQuat AngleToRotateQuat{ProjectileDirection.GetUpVector(), AngleToRotate};

					auto FinalQuat = AngleToRotateQuat * ProjectileDirection;
					Rotations.Add(FinalQuat);
					
					const auto Velocity = ProjectileInfoView[Index].InitialSpeed * FinalQuat.GetForwardVector();
					InitialVelocities.Add(Velocity);
				}
			}
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
