// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassAbilityInitializeTreeLeafsTask.h"

#include "MassEntityManager.h"
#include "MassEntityView.h"
#include "RemEventSchedulerExecutionContext.h"
#include "Event/RemMassInventoryInitialized.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"

FRemMassAbilityInitializeTreeLeafsTask::FRemMassAbilityInitializeTreeLeafsTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FRemMassAbilityInitializeTreeLeafsTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& EventContext = static_cast<FRemEventSchedulerExecutionContext&>(Context);
	const auto& [Manager, OwnerEntity, InitialItemEntities] = EventContext.EventData.Get<FRemMassInventoryInitialized>();

	RemCheckCondition(Manager && InitialItemEntities, return EStateTreeRunStatus::Failed, REM_NO_LOG_BUT_ENSURE);
	
	FMassEntityHandle RootNode{};
	FMassEntityHandle LastNode{};

	RemCheckCondition(InitialItemEntities->Num() > 1, return EStateTreeRunStatus::Failed, REM_NO_LOG_BUT_ENSURE);
	
	// make ability link list
	for (auto& InitialItemPair : *InitialItemEntities)
	{
		auto& Items = InitialItemPair.Value;

		bool bValidRoot = RootNode.IsValid();
		if (!bValidRoot && Items.Num() > 0)
		{
			LastNode = RootNode = Items[0];
		}
		
		for (int32 Index = 0; Index < Items.Num(); ++Index)
		{
			// add children node, skipped for root node to prevent infinite loop
			if (bValidRoot)
			{
				const auto& MassEntityHandle = Items[Index];
				const FMassEntityView EntityView{*Manager, LastNode};
				auto& ChildrenNodes = EntityView.GetFragmentData<FRemMassAbilityTreeChildrenNodesFragment>();
				ChildrenNodes.Add(MassEntityHandle);
				LastNode = MassEntityHandle;
			}
			else
			{
				bValidRoot = true;
			}
		}
	}

	const FMassEntityView OwnerView{*Manager, OwnerEntity};
	auto& TreeRootsFragment = OwnerView.GetFragmentData<FRemMassAbilityTreeRootsFragment>();
	
	// initialize tree leafs
	TreeRootsFragment.Values[0] = RootNode;

	FRemMassProjectileInfoFragment ProjectileInfoFragment;
	ProjectileInfoFragment.Efficient = 0.0f;
	ProjectileInfoFragment.InitialSpeed = 0.0f;

	FRemMassProjectileTriggerInfoFragment TriggerInfoFragment;
	TriggerInfoFragment.TriggerInterval = 0.0f;
	TriggerInfoFragment.RoundsPerInterval = 0;
	TriggerInfoFragment.RoundsInterval = 0.0f;
	TriggerInfoFragment.ShotsPerRound = 0;
	TriggerInfoFragment.ShotsInterval = 0.0f;
	// traverse tree leaf to generate projectile spawner
	DeepFirstSearch(*Manager, TreeRootsFragment.Values, TreeRootsFragment.Values.Num(), TriggerInfoFragment, ProjectileInfoFragment);
	
	return EStateTreeRunStatus::Succeeded;
}

void FRemMassAbilityInitializeTreeLeafsTask::DeepFirstSearch(const FMassEntityManager& Manager,
	const Rem::Mass::Ability::FTreeNodeEntityArray& Values, const Rem::Mass::Ability::FTreeNodeNumType Num,
	const FRemMassProjectileTriggerInfoFragment& TriggerInfo, const FRemMassProjectileInfoFragment Info)
{
	for (Rem::Mass::Ability::FTreeNodeNumType Index = 0; Index < Num; ++Index)
	{
		auto& EntityHandle = Values[Index];
		if (!EntityHandle.IsValid() || !Manager.IsEntityValid(EntityHandle))
		{
			continue;
		}
			
		const FMassEntityView EntityView{Manager, EntityHandle};
		auto& TriggerFragment = EntityView.GetFragmentData<FRemMassProjectileTriggerInfoFragment>();
		auto& ProjectileInfo = EntityView.GetFragmentData<FRemMassProjectileInfoFragment>();

		TriggerFragment.Combine(TriggerInfo);
		ProjectileInfo.Combine(Info);
			
		const auto& ChildNodesFragment = EntityView.GetFragmentData<FRemMassAbilityTreeChildrenNodesFragment>();
		DeepFirstSearch(Manager, ChildNodesFragment.GetValues(), ChildNodesFragment.GetNum(), TriggerFragment, ProjectileInfo);
	}
}
