// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDInitializerProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassHUDEntitySpawnData.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"

URemMassHUDInitializerProcessor::URemMassHUDInitializerProcessor()
{
	bAutoRegisterWithProcessingPhases = false;
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::FrameEnd;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::HUD;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Respawn);
}

void URemMassHUDInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassHUDBindingFragment>(EMassFragmentAccess::ReadWrite);
		
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassHUDInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassHUDInitializerProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& [SpawnData] = Context.GetAuxData().Get<FRemMassHUDEntitySpawnDataContainer>();
		const auto NumEntities = Context.GetNumEntities();

		RemCheckCondition(SpawnData.Num() <= NumEntities, return);

		const auto HUDBindingView = Context.GetMutableFragmentView<FRemMassHUDBindingFragment>();

		const auto MinNum = FMath::Min(NumEntities, SpawnData.Num());
		for(int32 EntityIndex = 0; EntityIndex < MinNum; ++EntityIndex)
		{
			auto& Binding = HUDBindingView[EntityIndex];
			Binding = SpawnData[EntityIndex];
		}
	});
}
