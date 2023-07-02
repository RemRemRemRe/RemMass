// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassRespawnProcessor.h"

#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "RemMassAbilityTags.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "Engine/CurveTable.h"
#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

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

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadOnly);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassRespawnProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassRespawnProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& GameStateSubsystem = Context.GetSubsystemChecked<URemMassGameStateSubsystem>();
		const auto& Manager = Context.GetEntityManagerChecked();
		
		const int32 NumEntities = Context.GetNumEntities();

		// respawn
		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
		const auto RespawnRadiusView = Context.GetFragmentView<FRemMassRespawnRadiusFragment>();

		// experience handling
		const auto ExperienceTypeView = Context.GetFragmentView<FRemMassExperienceTypeFragment>();

		for (auto& PlayerEntityHandle : GameStateSubsystem.GetPlayerEntityView())
		{
			const auto& PlayerTransform = Manager.GetFragmentDataChecked<FTransformFragment>(PlayerEntityHandle);
			const auto PlayerLocation = PlayerTransform.GetTransform().GetLocation();
			const auto ForwardDirection = PlayerTransform.GetTransform().GetRotation().GetForwardVector();

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

					auto& PlayerExperience = Manager.GetFragmentDataChecked<FRemMassExperienceFragment>(PlayerEntityHandle);
					
					// adding experience value
					{
						static const auto ContextString = FString{TEXTVIEW("adding experience value")};
						const auto* Curve = Manager.GetFragmentDataChecked<FRemMassLevelCurveTableFragment>(PlayerEntityHandle)
							.Value->FindCurve(RemMassAbilityTags.GetExpGainPerLevelTag().GetTagName(), ContextString);
						
						RemCheckVariable(Curve, continue;);
						
						const auto ExpGain = Curve->Eval(static_cast<float>(ExperienceTypeView[EntityIndex].Value) + 1.0f, 0.0f);

						PlayerExperience.Value += static_cast<int32>(ExpGain);
					}

					// level up
					{
						static const auto ContextString = FString{TEXTVIEW("level up")};
						const auto* Curve = Manager.GetFragmentDataChecked<FRemMassLevelCurveTableFragment>(PlayerEntityHandle)
							.Value->FindCurve(RemMassAbilityTags.GetRequiredExpToLevelUpTag().GetTagName(), ContextString);
						
						RemCheckVariable(Curve, continue;);

						auto& PlayerLevel = Manager.GetFragmentDataChecked<FRemMassLevelFragment>(PlayerEntityHandle);
						if (const auto RequiredExpToLevelUp = Curve->Eval(PlayerLevel.Value,
							std::numeric_limits<float>::max());
							PlayerExperience.Value >= static_cast<int32>(RequiredExpToLevelUp))
						{
							PlayerExperience.Value = {};
							PlayerLevel.Value++;
						}
					}
				}
			}
		}
	});
}
