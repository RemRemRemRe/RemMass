// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDInitializerProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassHUDEntitySpawnData.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"

URemMassHUDInitializerProcessor::URemMassHUDInitializerProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::FrameEnd;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::HUD;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Respawn);
}

void URemMassHUDInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassHUDTextBlockBindingFragment>(EMassFragmentAccess::ReadWrite);
		
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassHUDInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& [SpawnData] = Context.GetAuxData().Get<FRemMassHUDEntitySpawnDataContainer>();
		const auto NumEntities = Context.GetNumEntities();

		RemCheckCondition(SpawnData.Num() <= NumEntities, return);

		const auto HUDBindingView = Context.GetMutableFragmentView<FRemMassHUDTextBlockBindingFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			auto& Binding = HUDBindingView[EntityIndex];
			Binding = SpawnData[EntityIndex];
		}
	});
}
