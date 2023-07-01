// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDUpdateProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"

URemMassHUDUpdateProcessor::URemMassHUDUpdateProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::FrameEnd;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::HUD;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Respawn);
}

void URemMassHUDUpdateProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassHUDTextBlockBindingFragment>(EMassFragmentAccess::ReadOnly);
		
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassHUDUpdateProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
			const auto NumEntities = Context.GetNumEntities();

			const auto HUDBindingView = Context.GetMutableFragmentView<FRemMassHUDTextBlockBindingFragment>();

			for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				auto& Binding = HUDBindingView[EntityIndex];
			}
		});
	}
