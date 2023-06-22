// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassRespawnProcessor.h"

#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassRespawnProcessor)

URemMassRespawnProcessor::URemMassRespawnProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Respawn;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Damage);
}

void URemMassRespawnProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		// TODO make this shared fragment in 5.3
		.AddRequirement<FRemMassRespawnRadiusFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassDeadTag>(EMassFragmentPresence::All);
	
	EntityQuery.RegisterWithProcessor(*this);

	PlayerEntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassLocalPlayerTag>(EMassFragmentPresence::All);
	
	PlayerEntityQuery.RegisterWithProcessor(*this);
}

void URemMassRespawnProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassRespawnProcessor);
	
	int32 NumPlayers{};
	TConstArrayView<FTransformFragment> PlayerTransformView{};
	
	// ReSharper disable once CppDeclarationHidesLocal
	PlayerEntityQuery.ForEachEntityChunk(EntityManager, Context, [&](const FMassExecutionContext& Context)
	{
		NumPlayers = Context.GetNumEntities();

		PlayerTransformView = Context.GetFragmentView<FTransformFragment>();
	});
	
	RemCheckCondition(NumPlayers > 0, return;);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const int32 NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
		const auto& RespawnRadius = Context.GetFragmentView<FRemMassRespawnRadiusFragment>();

		for (int32 PlayerIndex = 0; PlayerIndex < NumPlayers; ++PlayerIndex)
		{
			const auto PlayerLocation = PlayerTransformView[PlayerIndex].GetTransform().GetLocation();
			const auto ForwardDirection = PlayerTransformView[PlayerIndex].GetTransform().GetRotation().GetForwardVector();

			for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				auto& EntityTransform = TransformView[EntityIndex].GetMutableTransform();

				const auto SpawnYawAngle = FMath::RandRange(0.0f, 360.0f);

				const FRotator YawOffset = {0.0f, SpawnYawAngle, 0.0f};

				const auto RotatedForward = YawOffset.RotateVector(ForwardDirection);

				const auto RespawnLocation = PlayerLocation + RotatedForward * RespawnRadius[EntityIndex].Value;
				
				EntityTransform.SetLocation(RespawnLocation);
				HealthView[EntityIndex] = {};
				
				Context.Defer().RemoveTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
			}
		}
	});
}
