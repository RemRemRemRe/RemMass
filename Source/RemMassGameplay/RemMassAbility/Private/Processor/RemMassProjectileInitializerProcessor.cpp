// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassProjectileInitializerProcessor.h"

#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassMovementFragments.h"
#include "ProjectileSpawnData.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassAbilityFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassProjectileInitializerProcessor)

URemMassProjectileInitializerProcessor::URemMassProjectileInitializerProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Initializer;
	bAutoRegisterWithProcessingPhases = false;
}

void URemMassProjectileInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassProjectileTag>(EMassFragmentPresence::All);

	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassProjectileInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassProjectileInitializerProcessor);

	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& [Locations, Rotations, InitialVelocities]
			= Context.GetAuxData().Get<FRemProjectileSpawnData>();

		const auto NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();
		const auto VelocityView = Context.GetMutableFragmentView<FMassVelocityFragment>();

		for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			TransformView[EntityIndex].SetTransform({Rotations[EntityIndex], Locations[EntityIndex]});
			VelocityView[EntityIndex].Value = InitialVelocities[EntityIndex];
		}
	});
}
