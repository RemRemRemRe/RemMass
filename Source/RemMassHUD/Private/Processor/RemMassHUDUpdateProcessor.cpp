// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDUpdateProcessor.h"

#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

URemMassHUDUpdateProcessor::URemMassHUDUpdateProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::HUD;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Experience);

	bRequiresGameThreadExecution = true;
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
		const auto LocalPlayerEntity = GameStateSubsystem.GetLocalPlayerEntity();
		
		RemEnsureVariable(LocalPlayerEntity, return;, REM_NO_LOG_AND_ASSERTION);

		const auto LocalPlayerEntityView = FMassEntityView{Context.GetEntityManagerChecked(), LocalPlayerEntity};
		
		const auto NumEntities = Context.GetNumEntities();
		
		const auto HUDBindingView = Context.GetFragmentView<FRemMassHUDBindingFragment>();

		TMap<const UScriptStruct*, FConstStructView> StructViewCache;
		
		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			auto& Binding = HUDBindingView[EntityIndex];

			RemEnsureVariable(Binding, continue;, REM_NO_LOG_AND_ASSERTION);

			TArray<FConstStructView> Views{};
			Views.Reserve(Binding.FragmentTypes.Num());

			Algo::Transform(Binding.FragmentTypes, Views, [&](const TWeakObjectPtr<const UScriptStruct> ScriptStruct)
			{
				auto* Key = ScriptStruct.Get();
				if (const auto* View = StructViewCache.Find(Key))
				{
					return *View;
				}
				
				const auto StructView = LocalPlayerEntityView.GetFragmentDataStruct(Key);

				RemCheckVariable(StructView, , REM_NO_LOG_AND_ASSERTION);

				StructViewCache.Add(Key, StructView);
				
				return FConstStructView{StructView};
			});
			
			Binding.UpdateWidget(Views);
		}
	});
}
