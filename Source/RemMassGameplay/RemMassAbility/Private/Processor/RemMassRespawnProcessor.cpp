// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassRespawnProcessor.h"

#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "RemMassAbilityTags.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "Engine/CurveTable.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassRespawnProcessor)

URemMassRespawnProcessor::URemMassRespawnProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Respawn;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Damage);
}

void URemMassRespawnProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FRemMassHealthFragment>(EMassFragmentAccess::ReadWrite)
		// TODO make this shared fragment in 5.3
		.AddRequirement<FRemMassRespawnRadiusFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassExperienceTypeFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassDeadTag>(EMassFragmentPresence::All);
	
	EntityQuery.RegisterWithProcessor(*this);

	PlayerEntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassLevelCurveTableFragment>(EMassFragmentAccess::ReadOnly)
		.AddRequirement<FRemMassExperienceFragment>(EMassFragmentAccess::ReadWrite)
		.AddRequirement<FRemMassLevelFragment>(EMassFragmentAccess::ReadWrite)
		.AddTagRequirement<FRemMassLocalPlayerTag>(EMassFragmentPresence::All);
	
	PlayerEntityQuery.RegisterWithProcessor(*this);
}

void URemMassRespawnProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassRespawnProcessor);
	
	int32 NumPlayers{};

	// respawn
	TConstArrayView<FTransformFragment> PlayerTransformView{};

	// experience handling
	TConstArrayView<FRemMassLevelCurveTableFragment> PlayerCurveTableView{};
	TArrayView<FRemMassExperienceFragment> PlayerExperienceView{};
	TArrayView<FRemMassLevelFragment> PlayerLevelView{};
	
	// ReSharper disable once CppDeclarationHidesLocal
	PlayerEntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		NumPlayers = Context.GetNumEntities();

		// respawn
		PlayerTransformView = Context.GetFragmentView<FTransformFragment>();

		// experience handling
		PlayerCurveTableView = Context.GetFragmentView<FRemMassLevelCurveTableFragment>();
		PlayerExperienceView = Context.GetMutableFragmentView<FRemMassExperienceFragment>();
		PlayerLevelView = Context.GetMutableFragmentView<FRemMassLevelFragment>();
	});
	
	RemCheckCondition(NumPlayers > 0, return;);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const int32 NumEntities = Context.GetNumEntities();

		// respawn
		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
		const auto RespawnRadiusView = Context.GetFragmentView<FRemMassRespawnRadiusFragment>();

		// experience handling
		const auto ExperienceTypeView = Context.GetFragmentView<FRemMassExperienceTypeFragment>();

		for (int32 PlayerIndex = 0; PlayerIndex < NumPlayers; ++PlayerIndex)
		{
			const auto PlayerLocation = PlayerTransformView[PlayerIndex].GetTransform().GetLocation();
			const auto ForwardDirection = PlayerTransformView[PlayerIndex].GetTransform().GetRotation().GetForwardVector();

			for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				// respawn
				{
					auto& EntityTransform = TransformView[EntityIndex].GetMutableTransform();

					const auto SpawnYawAngle = FMath::RandRange(0.0f, 360.0f);

					const FRotator YawOffset = {0.0f, SpawnYawAngle, 0.0f};

					const auto RotatedForward = YawOffset.RotateVector(ForwardDirection);

					const auto RespawnLocation = PlayerLocation + RotatedForward * RespawnRadiusView[EntityIndex].Value;
					
					EntityTransform.SetLocation(RespawnLocation);
					HealthView[EntityIndex] = {};
					
					Context.Defer().RemoveTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
				}

				// experience handling
				{
					const auto& RemMassAbilityTags = Rem::Common::GetDefaultRef<URemMassAbilityTags>();

					// adding experience value
					{
						static const auto ContextString = FString{TEXTVIEW("adding experience value")};
						const auto* Curve = PlayerCurveTableView[PlayerIndex].Value->FindCurve(
							RemMassAbilityTags.GetExpGainPerLevelTag().GetTagName(), ContextString);
						
						RemCheckVariable(Curve, continue;);
						
						const auto ExpGain = Curve->Eval(static_cast<float>(ExperienceTypeView[EntityIndex].Value) + 1.0f, 0.0f);

						PlayerExperienceView[PlayerIndex].Value += static_cast<int32>(ExpGain);
					}

					// level up
					{
						static const auto ContextString = FString{TEXTVIEW("level up")};
						const auto* Curve = PlayerCurveTableView[PlayerIndex].Value->FindCurve(
							RemMassAbilityTags.GetRequiredExpToLevelUpTag().GetTagName(), ContextString);
						
						RemCheckVariable(Curve, continue;);

						if (const auto RequiredExpToLevelUp = Curve->Eval(PlayerLevelView[PlayerIndex].Value,
							std::numeric_limits<float>::max());
							PlayerExperienceView[PlayerIndex].Value >= static_cast<int32>(RequiredExpToLevelUp))
						{
							PlayerExperienceView[PlayerIndex].Value = {};
							PlayerLevelView[PlayerIndex].Value++;
						}
					}
				}
			}
		}
	});
}
