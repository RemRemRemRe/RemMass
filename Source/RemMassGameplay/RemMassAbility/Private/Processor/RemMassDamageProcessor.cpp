// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassDamageProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassProcessorGroupNames.h"
#include "RemMassStatics.inl"
#include "Fragment/RemMassAbilityFragments.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassDamageProcessor)

URemMassDamageProcessor::URemMassDamageProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ProcessingPhase = EMassProcessingPhase::EndPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Damage;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Movement);
}

void URemMassDamageProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassDamageTargetTag>(EMassFragmentPresence::All)
		.AddTagRequirement<FRemMassDeadTag>(EMassFragmentPresence::None);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadOnly);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassDamageProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassDamageProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& GameStateSubsystem = Context.GetSubsystemChecked<URemMassGameStateSubsystem>();
		
		const int32 NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
		
		for (auto& PlayerEntityHandle : GameStateSubsystem.GetPlayerEntityView())
		{
			auto PlayerEntityView = FMassEntityView{Context.GetEntityManagerChecked(), PlayerEntityHandle};
			
			for(int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				const auto EntityLocation = TransformView[EntityIndex].GetTransform().GetLocation();
				const auto PlayerLocation = PlayerEntityView.GetFragmentData<FTransformFragment>().GetTransform().GetLocation();

				const auto Distance = FVector::Dist2D(PlayerLocation, EntityLocation);

				if (const auto DamageRadius = PlayerEntityView.GetFragmentData<FRemMassDamageRadiusFragment>().Value;
					Distance < DamageRadius)
				{
					HealthView[EntityIndex].Value -= PlayerEntityView.GetFragmentData<FRemMassDamageFragment>().Value;

					if (HealthView[EntityIndex].IsDead())
					{
						// lose health when killing
						PlayerEntityView.GetFragmentData<FRemMassHealthFragment>().Value -= FMath::RandRange(0.0f, 1.0f);
						
						Context.Defer().AddTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
					}
				}
			}
		}
	});
}
