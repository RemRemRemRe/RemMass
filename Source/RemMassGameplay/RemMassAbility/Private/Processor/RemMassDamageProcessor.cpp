// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassDamageProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "RemMassStatics.inl"
#include "Fragment/RemMassAbilityFragments.h"
#include "Subsystems/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassDamageProcessor)

URemMassDamageProcessor::URemMassDamageProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Damage;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassDamageProcessor::ConfigureQueries()
{
	DamageSourceEntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassDamageRadiusFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassDamageFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassDamageSourceTag>(EMassFragmentPresence::All)
		.AddTagRequirement<FRemMassDeadTag>(EMassFragmentPresence::None);

	DamageSourceEntityQuery.RegisterWithProcessor(*this);
	
	DamageTargetEntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassDamageTargetTag>(EMassFragmentPresence::All)
		.AddTagRequirement<FRemMassDeadTag>(EMassFragmentPresence::None);

	DamageTargetEntityQuery.RegisterWithProcessor(*this);
}

void URemMassDamageProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassDamageProcessor);

	int32 DamageSourceNum{0};
	TConstArrayView<FMassEntityHandle> DamageSourceEntityView;
	TConstArrayView<FTransformFragment> DamageSourceTransformView;
	TConstArrayView<FRemMassDamageRadiusFragment> DamageSourceRadiusView;
	TConstArrayView<FRemMassDamageFragment> DamageSourceDamageView;
	TArrayView<FRemMassHealthFragment> DamageSourceHealthView;
	
	// ReSharper disable once CppDeclarationHidesLocal
	DamageSourceEntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		DamageSourceNum = Context.GetNumEntities();
		DamageSourceEntityView = Context.GetEntities();
		DamageSourceTransformView = Context.GetFragmentView<FTransformFragment>();
		DamageSourceRadiusView = Context.GetFragmentView<FRemMassDamageRadiusFragment>();
		DamageSourceDamageView = Context.GetFragmentView<FRemMassDamageFragment>();
		DamageSourceHealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
	});
	
	// ReSharper disable once CppDeclarationHidesLocal
	DamageTargetEntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();

		for (int32 DamageSourceIndex = 0; DamageSourceIndex < DamageSourceNum; ++DamageSourceIndex)
		{
			for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				const auto EntityLocation = TransformView[EntityIndex].GetTransform().GetLocation();
				const auto DamageSourceLocation = DamageSourceTransformView[DamageSourceIndex].GetTransform().GetLocation();

				const auto Distance = FVector::Dist2D(DamageSourceLocation, EntityLocation);

				if (const auto DamageRadius = DamageSourceRadiusView[DamageSourceIndex].Value;
					Distance < DamageRadius)
				{
					HealthView[EntityIndex].Value -= DamageSourceDamageView[DamageSourceIndex].Value;

					// lose health when damaging
					DamageSourceHealthView[DamageSourceIndex].Value -= FMath::RandRange(0.5f, 1.0f);
					if (DamageSourceHealthView[DamageSourceIndex].IsDead())
					{
						Context.Defer().DestroyEntity(DamageSourceEntityView[DamageSourceIndex]);
					}
					
					if (HealthView[EntityIndex].IsDead())
					{
						Context.Defer().AddTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
					}
				}
			}
		}
	});
}
