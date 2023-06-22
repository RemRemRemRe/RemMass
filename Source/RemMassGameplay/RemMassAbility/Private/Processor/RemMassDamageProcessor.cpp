// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassDamageProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassDamageProcessor)

URemMassDamageProcessor::URemMassDamageProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Damage;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassDamageProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassDamageTargetTag>(EMassFragmentPresence::All);
	
	EntityQuery.RegisterWithProcessor(*this);

	PlayerEntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassDamageRadiusFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassDamageFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassLocalPlayerTag>(EMassFragmentPresence::All)
		.AddTagRequirement<FRemMassDamageSourceTag>(EMassFragmentPresence::All);
	
	PlayerEntityQuery.RegisterWithProcessor(*this);
}

void URemMassDamageProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassDamageProcessor);

	int32 NumPlayers{};
	TConstArrayView<FTransformFragment> PlayerTransformView{};
	TConstArrayView<FRemMassDamageRadiusFragment> PlayerDamageRadiusView{};
	TConstArrayView<FRemMassDamageFragment> PlayerDamageView{};
	
	// ReSharper disable once CppDeclarationHidesLocal
	PlayerEntityQuery.ForEachEntityChunk(EntityManager, Context, [&](const FMassExecutionContext& Context)
	{
		NumPlayers = Context.GetNumEntities();

		PlayerTransformView = Context.GetFragmentView<FTransformFragment>();
		PlayerDamageRadiusView = Context.GetFragmentView<FRemMassDamageRadiusFragment>();
		PlayerDamageView = Context.GetFragmentView<FRemMassDamageFragment>();
	});
	
	RemCheckCondition(NumPlayers > 0, return;);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const int32 NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();

		for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			const auto EntityLocation = TransformView[EntityIndex].GetTransform().GetLocation();
			
			for (int32 PlayerIndex = 0; PlayerIndex < NumPlayers; ++PlayerIndex)
			{
				const auto PlayerLocation = PlayerTransformView[PlayerIndex].GetTransform().GetLocation();

				const auto Distance = FVector::Dist2D(PlayerLocation, EntityLocation);

				if (const auto DamageRadius = PlayerDamageRadiusView[PlayerIndex].Value;
					Distance < DamageRadius)
				{
					HealthView[EntityIndex].Value -= PlayerDamageView[PlayerIndex].Value;

					if (HealthView[EntityIndex].IsDead())
					{
						Context.Defer().AddTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
					}
				}
			}
		}
	});
}
