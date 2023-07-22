// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassOnPlayerAddedProcessor.h"

#include "MassActorSubsystem.h"
#include "MassExecutionContext.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"
#include "Translators/MassCharacterMovementTranslators.h"
#include "Translators/MassSceneComponentLocationTranslator.h"

URemMassOnPlayerAddedProcessor::URemMassOnPlayerAddedProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::AllNetModes);
	ObservedType = FRemMassPlayerFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
	bRequiresGameThreadExecution = true;
}

void URemMassOnPlayerAddedProcessor::Register()
{
	Super::Register();
}

void URemMassOnPlayerAddedProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMassSceneComponentWrapperFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassPlayerFragment>(EMassFragmentAccess::ReadOnly);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadWrite);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassOnPlayerAddedProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassOnPlayerAddedProcessor);

	// ReSharper disable once CppDeclarationHidesUncapturedLocal
	auto DelayExecute = [this, &EntityManager] (FMassExecutionContext Context)
	{
		// ReSharper disable once CppDeclarationHidesUncapturedLocal
		EntityQuery.ForEachEntityChunk(EntityManager, Context, [](FMassExecutionContext& Context)
		{
			const auto NumEntities = Context.GetNumEntities();
			auto& GameStateSubsystem = Context.GetMutableSubsystemChecked<URemMassGameStateSubsystem>();

			const auto SceneComponentView = Context.GetFragmentView<FMassSceneComponentWrapperFragment>();
			
			for (int32 Index = 0; Index < NumEntities; ++Index)
			{
				RemCheckVariable(SceneComponentView[Index].Component, continue;, REM_NO_LOG_AND_ASSERTION);
				GameStateSubsystem.AddPlayerEntity(Cast<APawn>(SceneComponentView[Index].Component->GetOwner()));
			}
		});
	};
	
	Context.GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(
		this, DelayExecute, Context));
}
