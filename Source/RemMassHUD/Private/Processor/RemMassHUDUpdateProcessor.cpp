// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDUpdateProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

URemMassHUDUpdateProcessor::URemMassHUDUpdateProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::FrameEnd;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::HUD;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Respawn);
}

void URemMassHUDUpdateProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassHUDBindingFragment>(EMassFragmentAccess::ReadOnly);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadOnly);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassHUDUpdateProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassHUDUpdateProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& GameStateSubsystem = Context.GetSubsystemChecked<URemMassGameStateSubsystem>();
		const auto& Manager = Context.GetEntityManagerChecked();
		const auto LocalPlayerEntity = GameStateSubsystem.GetLocalPlayerEntity();
		
		const auto NumEntities = Context.GetNumEntities();

		const auto HUDBindingView = Context.GetFragmentView<FRemMassHUDBindingFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			auto& Binding = HUDBindingView[EntityIndex];

			const auto StructView = Manager.GetFragmentDataStruct(LocalPlayerEntity, Binding.FragmentType.Get());
			RemCheckVariable(StructView, continue;);
			
			Binding.UpdateWidget(StructView);
		}
	});
}
