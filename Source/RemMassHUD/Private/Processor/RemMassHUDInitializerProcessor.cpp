// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassHUDInitializerProcessor.h"

#include "MassExecutionContext.h"
#include "RemMassHUDEntitySpawnData.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassHUDFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDInitializerProcessor)

URemMassHUDInitializerProcessor::URemMassHUDInitializerProcessor()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Client);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Initializer;
	bAutoRegisterWithProcessingPhases = false;
}

void URemMassHUDInitializerProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRemMassHUDBindingFragment>(EMassFragmentAccess::ReadWrite);

	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassHUDInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassHUDInitializerProcessor);

	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(Context, [&](FMassExecutionContext& Context)
	{
		const auto& Data = Context.GetAuxData().Get<FRemMassHUDEntitySpawnDataContainer>();
		const auto NumEntities = Context.GetNumEntities();

		const auto HUDBindingView = Context.GetMutableFragmentView<FRemMassHUDBindingFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			auto& Binding = HUDBindingView[EntityIndex];
			Binding = Data.SpawnData[EntityIndex];
		}
	});
}
