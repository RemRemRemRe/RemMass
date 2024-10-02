// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassExpInitializerProcessor.h"

#include "ExperienceSpawnData.h"
#include "MassExecutionContext.h"
#include "MassCommonFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassAbilityFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassExpInitializerProcessor)

URemMassExpInitializerProcessor::URemMassExpInitializerProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Initializer;
	bAutoRegisterWithProcessingPhases = false;
}

void URemMassExpInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FRemMassExperienceTypeFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);

	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassExpInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassExpInitializerProcessor);

	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& Value = Context.GetAuxData().Get<FRemExperienceSpawnDataContainer>();
		const auto NumEntities = Context.GetNumEntities();

		const auto ExperienceTypeView = Context.GetMutableFragmentView<FRemMassExperienceTypeFragment>();
		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			ExperienceTypeView[EntityIndex] = Value.ExpTypeData[EntityIndex];
			TransformView[EntityIndex] = Value.TransformData[EntityIndex];
		}
	});
}
