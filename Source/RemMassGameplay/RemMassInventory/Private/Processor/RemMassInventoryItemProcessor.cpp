// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassInventoryItemProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassInventoryLog.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemLogMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassInventoryItemProcessor)

namespace Rem::Mass::Inventory
{

#if REM_WITH_DEVELOPMENT_ONLY_CODE

	static FAutoConsoleVariable CVarPrintInventoryItemData(TEXT("Rem.Mass.Inventory.PrintInventoryItemData"),
		false, TEXT("whether to print inventory item data"));

#endif

}

URemMassInventoryItemProcessor::URemMassInventoryItemProcessor()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::FrameEnd;
}

void URemMassInventoryItemProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRemMassOwnerFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassInventoryItemTagFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassInventoryItemCountFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassInventoryItemStateFragment>(EMassFragmentAccess::ReadOnly)

		.AddTagRequirement<FRemMassInventoryItemTag>(EMassFragmentPresence::All);

	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassInventoryItemProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassExperienceCollectorProcessor);

#if REM_WITH_DEVELOPMENT_ONLY_CODE

	if (!Rem::Mass::Inventory::CVarPrintInventoryItemData->GetBool())
	{
		return;
	}

#endif

	static int32 FrameInterval = 120;
	static int32 Counter = 0;

	if (++Counter;
		Counter < FrameInterval)
	{
		return;
	}

	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(Context, [&](const FMassExecutionContext& Context)
	{
		const auto NumEntities = Context.GetNumEntities();

		const auto ItemOwnerView = Context.GetFragmentView<FRemMassOwnerFragment>();
		const auto ItemTagView = Context.GetFragmentView<FRemMassInventoryItemTagFragment>();
		const auto ItemCountView = Context.GetFragmentView<FRemMassInventoryItemCountFragment>();
		const auto ItemStateView = Context.GetFragmentView<FRemMassInventoryItemStateFragment>();

		for (int32 Index = 0; Index < NumEntities; ++Index)
		{
			REM_LOG_FUNCTION(LogRemMassInventory, Log, TEXT("Owner: {0}, Tag: {1}, Count: {2}, State: {3}"),
				ItemOwnerView[Index].Value.DebugGetDescription(), ItemTagView[Index], ItemCountView[Index], ItemStateView[Index]);
		}

	});
}
