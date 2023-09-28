// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassAbilityInitializeTreeLeafsTask.h"

#include "DataRegistrySource.h"
#include "MassEntityView.h"
#include "RemDataRegistryStatics.h"
#include "RemEventSchedulerExecutionContext.h"
#include "Event/RemMassInventoryInitialized.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemAssertionMacros.h"

FRemMassAbilityInitializeTreeLeafsTask::FRemMassAbilityInitializeTreeLeafsTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FRemMassAbilityInitializeTreeLeafsTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const auto& EventContext = static_cast<FRemEventSchedulerExecutionContext&>(Context);
	const auto& [Manager, OwnerEntity, Entities] = EventContext.EventData.Get<FRemMassInventoryItemsInitialized>();

	RemCheckCondition(Manager && Entities, return EStateTreeRunStatus::Failed, REM_NO_LOG_BUT_ENSURE);
	
	auto& Items = Entities->Value;
	
	// make ability link list
	for (int32 Index = 1; Index < Items.Num(); ++Index)
	{
		auto& ItemHandle = Items[Index];

		const FMassEntityView View{*Manager, ItemHandle};
		View.GetFragmentData<FRemMassAbilityTreePreviousNodeFragment>().Value = Items[Index - 1];

		auto& ItemTag = View.GetFragmentData<FRemMassInventoryItemTagFragment>().Value;
		
		// find data table row, and apply spawner data
		Rem::DataRegistry::LoadRegistryItemThen(ItemTag, FDataRegistryItemAcquiredCallback::CreateLambda(
			[&](const FDataRegistryAcquireResult& Result)
		{
			if (Result.Status == EDataRegistryAcquireStatus::AcquireFinished)
			{
				auto* ItemData = Result.GetItem<FRemMassProjectileSpawnerFragment>();
				RemCheckVariable(ItemData, return);

				View.GetFragmentData<FRemMassProjectileSpawnerFragment>() = *ItemData;
			}
		}));
	}

	const FMassEntityView OwnerView{*Manager, OwnerEntity};
	auto& TreeLeafsFragment = OwnerView.GetFragmentData<FRemMassAbilityTreeLeafsFragment>();
	
	// initialize tree leafs
	TreeLeafsFragment.Values[0][0] = {Items[Items.Num() - 1]};
	
	// traverse tree leaf to generate projectile spawner
	for (int32 Index = 0; Index < TreeLeafsFragment.Values.Num(); ++Index)
	{
		
		for (auto& TreeLeafsArray = TreeLeafsFragment.Values[Index];
		     const auto& LeafNode : TreeLeafsArray)
		{
			if (!LeafNode.IsValid())
			{
				continue;
			}
			
			const FMassEntityView LeafView = {*Manager, LeafNode};

			
		}
	}
	return FMassStateTreeTaskBase::EnterState(Context, Transition);
}
