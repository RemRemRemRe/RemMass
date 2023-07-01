// Copyright RemRemRemRe, All Rights Reserved.


#include "Subsystem/RemMassGameStateSubsystem.h"

#include "MassAgentComponent.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"
#include "Object/RemObjectStatics.h"

DEFINE_LOG_CATEGORY(LogRemMassGameState)

auto URemMassGameStateSubsystem::GetLocalPlayerEntityHandle() const -> FMassEntityHandle
{
	if (!PlayerActors.IsEmpty() && PlayerActors[0] && PlayerActors[0]->IsLocallyControlled())
	{
		return PlayerEntityHandles[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::GetLocalPlayerPawn() const -> const APawn*
{
	if (!PlayerActors.IsEmpty() && PlayerActors[0] && PlayerActors[0]->IsLocallyControlled())
	{
		return PlayerActors[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::AddPlayerEntity(const APawn* PlayerPawn) -> void
{
	RemCheckVariable(PlayerPawn, return;);
	
	const auto* Agent = PlayerPawn->FindComponentByClass<UMassAgentComponent>();
	RemCheckVariable(Agent, return;);
	
	RemCheckCondition(!Agent->IsEntityPendingCreation(), return;);
	
	if (PlayerPawn->IsLocallyControlled())
	{
		PlayerActors.Insert(PlayerPawn, 0);
		PlayerEntityHandles.Insert(Agent->GetEntityHandle(), 0);
	}
	else
	{
		PlayerActors.Add(PlayerPawn);
		PlayerEntityHandles.Add(Agent->GetEntityHandle());
	}
}

auto URemMassGameStateSubsystem::Initialize(FSubsystemCollectionBase& Collection) -> void
{
	Super::Initialize(Collection);

	const auto* World = GetWorld();
	if (World->IsNetMode(NM_DedicatedServer))
	{
		return;
	}
	
	if (const auto* Pawn = URemObjectStatics::GetFirstLocalPlayerPawn(World))
	{
		const auto* Agent = Pawn->FindComponentByClass<UMassAgentComponent>();
		RemCheckVariable(Agent, return;);

		if (!Agent->IsEntityPendingCreation())
		{
			PlayerActors.Insert(Pawn, 0);
			PlayerEntityHandles.Insert(Agent->GetEntityHandle(), 0);
		}
		else
		{
			REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Entity is pending creation for pawn{0}"), Pawn);
		}
	}
	else
	{
		REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Didn't find valid local pawn"));
	}
}
