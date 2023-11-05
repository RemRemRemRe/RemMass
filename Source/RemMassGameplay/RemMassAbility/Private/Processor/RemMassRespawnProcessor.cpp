// Copyright RemRemRemRe, All Rights Reserved.


#include "Processor/RemMassRespawnProcessor.h"

#include "MassCommonFragments.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "RemMassAbilityTags.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "RemMassProcessorGroupNames.h"
#include "RemMassStatics.inl"
#include "Macro/RemAssertionMacros.h"
#include "SpawnDataGenerator/RemMassExperienceRegenerator.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

namespace
{

#if REM_WITH_DEVELOPMENT_ONLY_CODE

	FAutoConsoleVariable CVarDisableRespawnRandomYawOffset{TEXT("Rem.Mass.Respawn.DisableRandomYawOffset"), false, TEXT(""), ECVF_Cheat};

#endif

}

URemMassRespawnProcessor::URemMassRespawnProcessor()
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);
	ProcessingPhase = EMassProcessingPhase::DuringPhysics;
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
		
		const auto NumEntities = Context.GetNumEntities();

		// respawn
		const auto TransformView = Context.GetMutableFragmentView<FTransformFragment>();
		const auto HealthView = Context.GetMutableFragmentView<FRemMassHealthFragment>();
		const auto RespawnRadiusView = Context.GetFragmentView<FRemMassRespawnRadiusFragment>();

		// experience handling
		const auto ExperienceTypeView = Context.GetFragmentView<FRemMassExperienceTypeFragment>();

		const auto PlayerView = GameStateSubsystem.GetPlayerEntityView();
		RemCheckCondition(PlayerView.Num() > 0, return, REM_NO_LOG_BUT_ENSURE);

		const auto PlayerEntityView = FMassEntityView{Context.GetEntityManagerChecked(), PlayerView[0]};

		const auto& PlayerTransform = PlayerEntityView.GetFragmentData<FTransformFragment>();
		const auto PlayerLocation = PlayerTransform.GetTransform().GetLocation();
		const auto ForwardDirection = PlayerTransform.GetTransform().GetRotation().GetForwardVector();

		TArray<FTransformFragment> SavedTransformArray{TransformView};
		for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			auto& EntityTransform = TransformView[EntityIndex].GetMutableTransform();

			const auto SpawnYawAngle = FMath::RandRange(0.0f, 360.0f);

			const FRotator YawOffset = {0.0f, SpawnYawAngle, 0.0f};

			const auto RotatedForward = YawOffset.RotateVector(ForwardDirection);

#if REM_WITH_DEVELOPMENT_ONLY_CODE
			
			const auto RespawnLocation = PlayerLocation +
				(CVarDisableRespawnRandomYawOffset->GetBool() ? ForwardDirection : RotatedForward) * RespawnRadiusView[EntityIndex].Value;
			
#elif

			const auto RespawnLocation = PlayerLocation + RotatedForward * RespawnRadiusView[EntityIndex].Value;
			
#endif
			
			EntityTransform.SetLocation(RespawnLocation);
			HealthView[EntityIndex] = {};

			Context.Defer().RemoveTag<FRemMassDeadTag>(Context.GetEntity(EntityIndex));
		}

		Context.Defer().PushCommand<FMassDeferredCreateCommand>([ExperienceTypeView, MovedTransformArray = std::move(SavedTransformArray)]
		(const FMassEntityManager& Manager)
		{
			auto* EntityGenerator = Rem::Mass::GetSpawnDataGenerator<URemMassExperienceRegenerator>(
				Manager.GetWorld(),
				FGameplayTagQuery::MakeQuery_MatchTag(
					Rem::Common::GetDefaultRef<URemMassAbilityTags>().GetExpMassSpawnerTag()));
			RemCheckVariable(EntityGenerator, return;);

			Rem::Mass::FScopedEntitySpawnDataRegeneration ScopedEntityRegeneration{*EntityGenerator};
			
			EntityGenerator->AddSpawnData({ExperienceTypeView,  std::move(MovedTransformArray)});
		});
	});
}
