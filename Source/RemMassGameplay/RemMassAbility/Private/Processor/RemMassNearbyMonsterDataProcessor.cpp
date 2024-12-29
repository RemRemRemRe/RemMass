// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassNearbyMonsterDataProcessor.h"

#include "MassCommonFragments.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Subsystems/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassNearbyMonsterDataProcessor)

URemMassNearbyMonsterDataProcessor::URemMassNearbyMonsterDataProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::AllNetModes);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::NearbyMonsterData;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassNearbyMonsterDataProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassMonsterTag>(EMassFragmentPresence::All);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadWrite);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassNearbyMonsterDataProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassNearbyMonsterDataProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		auto& GameStateSubsystem = Context.GetMutableSubsystemChecked<URemMassGameStateSubsystem>();
		
		const auto NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetFragmentView<FTransformFragment>();

		FRWScopeLock ScopeLock{GameStateSubsystem.PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
		FRWScopeLock ScopeDataLock{GameStateSubsystem.NearbyMonsterEntityLock, FRWScopeLockType::SLT_Write};
		
		const auto PlayerEntities = GameStateSubsystem.GetPlayerEntityView();
		
		for (int32 PlayerIndex = 0; PlayerIndex < PlayerEntities.Num(); ++PlayerIndex)
		{
			const auto PlayerEntityView = FMassEntityView{Context.GetEntityManagerChecked(), PlayerEntities[PlayerIndex]};
			const auto& PlayerTransform = PlayerEntityView.GetFragmentData<FTransformFragment>();
			const auto PlayerLocation = PlayerTransform.GetTransform().GetLocation();
			
			for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				const auto EntityLocation = TransformView[EntityIndex].GetTransform().GetLocation();

				const auto DistanceSquared = FVector::DistSquared(PlayerLocation, EntityLocation);

				auto& MonsterData = GameStateSubsystem.GetNearbyMonsterEntityDataContainer();

				if (!LIKELY(MonsterData.NearbyMonsterEntityData.IsValidIndex(PlayerIndex)))
				{
					MonsterData.NearbyMonsterEntityData.AddDefaulted();
				}
				
				auto& NearbyMonsterEntityData = MonsterData.NearbyMonsterEntityData[PlayerIndex];

				if (const auto ExistingIndex = NearbyMonsterEntityData.NearbyMonsterHandles.Find(Context.GetEntity(EntityIndex));
					ExistingIndex != INDEX_NONE)
				{
					NearbyMonsterEntityData.RemoveAt(ExistingIndex);
				}
				
				const auto IndexFound = Algo::BinarySearch(NearbyMonsterEntityData.NearbyMonsterDistancesSquared,
					DistanceSquared);
				
				const auto IndexToInsert = IndexFound == INDEX_NONE ? 0 : IndexFound;
				
				NearbyMonsterEntityData.NearbyMonsterHandles.Insert(Context.GetEntity(EntityIndex), IndexToInsert);
				NearbyMonsterEntityData.NearbyMonsterDistancesSquared.Insert(DistanceSquared, IndexToInsert);
				{
					const auto Direction = (EntityLocation - PlayerLocation).GetSafeNormal2D();
					NearbyMonsterEntityData.NearbyMonsterDirections.Insert(Direction, IndexToInsert);
				}

				if (constexpr int32 MaxNearbyMonsterCount = 10;
					NearbyMonsterEntityData.NearbyMonsterHandles.Num() > MaxNearbyMonsterCount)
				{
					NearbyMonsterEntityData.RemoveAt(MaxNearbyMonsterCount);
				}
			}
		}
	});
}
