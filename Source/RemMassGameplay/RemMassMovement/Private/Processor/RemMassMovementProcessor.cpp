// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassMovementProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassLODFragments.h"
#include "MassMovementFragments.h"
#include "RemMassProcessorGroupNames.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassMovementProcessor)

URemMassMovementProcessor::URemMassMovementProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::AllNetModes);
	ProcessingPhase = EMassProcessingPhase::PrePhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Movement;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Movement);
}

void URemMassMovementProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FMassForceFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FMassOffLODTag>(EMassFragmentPresence::None);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassMovementProcessor);

	// ReSharper disable once CppDeclarationHidesUncapturedLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [](FMassExecutionContext& Context)
	{
		const auto NumEntities = Context.GetNumEntities();

		const auto LocationList = Context.GetMutableFragmentView<FTransformFragment>();
		const auto ForceList = Context.GetFragmentView<FMassForceFragment>();
		const auto VelocityList = Context.GetMutableFragmentView<FMassVelocityFragment>();

		for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			const auto& Force = ForceList[EntityIndex];
			auto& Velocity = VelocityList[EntityIndex];
			auto& CurrentTransform = LocationList[EntityIndex].GetMutableTransform();

			// Update velocity from steering forces.
			Velocity.Value += Force.Value * Context.GetDeltaTimeSeconds();

#if WITH_MASSGAMEPLAY_DEBUG
			if (UE::MassMovement::bFreezeMovement)
			{
				Velocity.Value = FVector::ZeroVector;
			}
#endif // WITH_MASSGAMEPLAY_DEBUG

			auto CurrentLocation = CurrentTransform.GetLocation();
			CurrentLocation += Velocity.Value * Context.GetDeltaTimeSeconds();
			CurrentTransform.SetTranslation(CurrentLocation);
		}
	});
}
