// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassExpInitializerProcessor.h"

#include "ExperienceSpawnData.h"
#include "MassExecutionContext.h"
#include "MassCommonFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassAbilityFragments.h"

URemMassExpInitializerProcessor::URemMassExpInitializerProcessor()
{
	bAutoRegisterWithProcessingPhases = false;
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Respawn;
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
		const auto& [ExpTypeData, TransformData] = Context.GetAuxData().Get<FRemExperienceSpawnDataContainer>();
		const auto NumEntities = Context.GetNumEntities();

		const auto ExperienceTypeView = Context.GetMutableFragmentView<FRemMassExperienceTypeFragment>();
		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			ExperienceTypeView[EntityIndex] = ExpTypeData[EntityIndex];
			TransformView[EntityIndex] = TransformData[EntityIndex];
		}
	});
}
