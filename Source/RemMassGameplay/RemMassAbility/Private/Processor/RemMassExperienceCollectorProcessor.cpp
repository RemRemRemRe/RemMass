// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassExperienceCollectorProcessor.h"

#include "MassCommonFragments.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassAbilityTags.h"
#include "RemMassProcessorGroupNames.h"
#include "Engine/CurveTable.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

URemMassExperienceCollectorProcessor::URemMassExperienceCollectorProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
	ExecutionOrder.ExecuteInGroup = Rem::Mass::ProcessorGroup::Name::Experience;
	ExecutionOrder.ExecuteAfter.Add(Rem::Mass::ProcessorGroup::Name::Respawn);
}

void URemMassExperienceCollectorProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly)
		// TODO make this shared fragment in 5.3
		.AddRequirement<FRemMassExperienceTypeFragment>(EMassFragmentAccess::ReadOnly)
		.AddTagRequirement<FRemMassExpItemTag>(EMassFragmentPresence::All);

	EntityQuery.AddSubsystemRequirement<URemMassGameStateSubsystem>(EMassFragmentAccess::ReadOnly);
	
	EntityQuery.RegisterWithProcessor(*this);
}

void URemMassExperienceCollectorProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(URemMassExperienceCollectorProcessor);
	
	// ReSharper disable once CppDeclarationHidesLocal
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [&](FMassExecutionContext& Context)
	{
		const auto& GameStateSubsystem = Context.GetSubsystemChecked<URemMassGameStateSubsystem>();

		const auto NumEntities = Context.GetNumEntities();

		const auto TransformView = Context.GetFragmentView<FTransformFragment>();
		const auto ExperienceTypeView = Context.GetFragmentView<FRemMassExperienceTypeFragment>();

		const auto& RemMassAbilityTags = Rem::Common::GetDefaultRef<URemMassAbilityTags>();

		TArray<FMassEntityHandle> CollectedExpEntities;
		bool bCheckIfCollected = false;

		FRWScopeLock ScopeLock{GameStateSubsystem.PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
		for (auto& PlayerEntityHandle : GameStateSubsystem.GetPlayerEntityView())
		{
			auto PlayerEntityView = FMassEntityView{Context.GetEntityManagerChecked(), PlayerEntityHandle};

			const auto& PlayerTransform = PlayerEntityView.GetFragmentData<FTransformFragment>();
			const auto PlayerLocation = PlayerTransform.GetTransform().GetLocation();
			//const auto ForwardDirection = PlayerTransform.GetTransform().GetRotation().GetForwardVector();

			const auto ExpCollectRadiusSquared = FMath::Square(PlayerEntityView.GetFragmentData<FRemMassExpCollectRadiusFragment>().Value);

			for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
			{
				const FMassEntityHandle Entity = Context.GetEntity(EntityIndex);
				
				if (bCheckIfCollected && CollectedExpEntities.Contains(Entity))
				{
					continue;
				}

				if (const auto DistanceSquared = FVector::DistSquared(
					TransformView[EntityIndex].GetTransform().GetLocation(), PlayerLocation);
					DistanceSquared > ExpCollectRadiusSquared)
				{
					continue;
				}
				
				auto& PlayerExperience = PlayerEntityView.GetFragmentData<FRemMassExperienceFragment>();

				const auto CurveTable = PlayerEntityView.GetFragmentData<FRemMassLevelCurveTableFragment>().Value.Get();

				RemCheckVariable(CurveTable, continue;, REM_NO_LOG_BUT_ENSURE);

				// adding experience value
				{
					static const auto ContextString = FString{TEXTVIEW("adding experience value")};
					const auto* Curve = CurveTable->FindCurve(RemMassAbilityTags.GetExpGainPerLevelTag().GetTagName(),
						ContextString);

					RemCheckVariable(Curve, continue;);

					const auto ExpGain = Curve->Eval(static_cast<float>(ExperienceTypeView[EntityIndex].Value) + 1.0f,
						0.0f);

					PlayerExperience.Value += static_cast<int32>(ExpGain);
				}

				// level up
				if (auto& LevelUpExperience = PlayerEntityView.GetFragmentData<FRemMassLevelUpExperienceFragment>();
						PlayerExperience.Value >= LevelUpExperience.Value)
				{
					static const auto ContextString = FString{TEXTVIEW("level up")};
					const auto* Curve = CurveTable->FindCurve(
						RemMassAbilityTags.GetRequiredExpToLevelUpTag().GetTagName(), ContextString);
					RemCheckVariable(Curve, continue;);

					auto& PlayerLevel = PlayerEntityView.GetFragmentData<FRemMassLevelFragment>();

					PlayerExperience.Value = {};
					PlayerLevel.Value++;

					LevelUpExperience.Value = Curve->Eval(PlayerLevel.Value, std::numeric_limits<int32>::max());
				}
				
				CollectedExpEntities.Add(Entity);

				// early out if all exp get collected
				if (CollectedExpEntities.Num() == NumEntities)
				{
					break;
				}
			}

			// early out if all exp get collected
			if (CollectedExpEntities.Num() == NumEntities)
			{
				break;
			}

			// check from the second round of loop
			bCheckIfCollected = true;
		}

		Context.Defer().DestroyEntities(CollectedExpEntities);
	});
}
