// Copyright RemRemRemRe, All Rights Reserved.


#include "Subsystem/RemMassGameStateSubsystem.h"

#include "MassAgentComponent.h"
#include "RemMassSpawner.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"
#include "Object/RemObjectStatics.h"

DEFINE_LOG_CATEGORY(LogRemMassGameState)

auto URemMassGameStateSubsystem::GetLocalPlayerEntity() const -> FMassEntityHandle
{
	FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_ReadOnly};
	
	if (!PlayerActors.IsEmpty() && PlayerActors[0] && PlayerActors[0]->IsLocallyControlled())
	{
		return PlayerEntityHandles[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::GetLocalPlayerPawn() const -> const APawn*
{
	FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_ReadOnly};
	
	if (!PlayerActors.IsEmpty() && PlayerActors[0] && PlayerActors[0]->IsLocallyControlled())
	{
		return PlayerActors[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::GetPlayerEntityView() const -> TConstArrayView<FMassEntityHandle>
{
	FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_ReadOnly};
	
	return {PlayerEntityHandles};
}

auto URemMassGameStateSubsystem::GetPlayerActorView() const -> TConstArrayView<APawn*>
{
	FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_ReadOnly};
	
	return {PlayerActors};
}

auto URemMassGameStateSubsystem::GetMassSpawner(const FGameplayTagQuery& SpawnerQuery) const -> ARemMassSpawner*
{
	for (auto* Spawner : MassSpawners)
	{
		RemCheckVariable(Spawner, continue;);

		if (SpawnerQuery.Matches(Spawner->GetActorTags()))
		{
			return Spawner;
		}
	}
	
	return {};
}

auto URemMassGameStateSubsystem::RegisterMassSpawner(ARemMassSpawner& MassSpawner) -> void
{
	MassSpawners.Add(&MassSpawner);
}

void URemMassGameStateSubsystem::AddPlayerEntity(APawn* PlayerPawn)
{
	RemCheckVariable(PlayerPawn, return;);
	
	const auto* Agent = PlayerPawn->FindComponentByClass<UMassAgentComponent>();
	RemCheckVariable(Agent, return;);
	
	RemCheckCondition(!Agent->IsEntityPendingCreation(), return;);
	
	{
		FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_Write};
		
		if (PlayerActors.Contains(PlayerPawn))
		{
			REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Pawn{0} already exist"), PlayerPawn);
			return;
		}
		
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
}

auto URemMassGameStateSubsystem::Initialize(FSubsystemCollectionBase& Collection) -> void
{
	Super::Initialize(Collection);

	const auto* World = GetWorld();
	if (World->IsNetMode(NM_DedicatedServer))
	{
		return;
	}

	auto* Pawn = URemObjectStatics::GetFirstLocalPlayerPawn(World);
	
	RemCheckVariable(Pawn, return;);
	
	const auto* Agent = Pawn->FindComponentByClass<UMassAgentComponent>();
	RemCheckVariable(Agent, return;);

	if (!Agent->IsEntityPendingCreation())
	{
		FRWScopeLock ScopeLock{Lock, FRWScopeLockType::SLT_Write};
		
		PlayerActors.Insert(Pawn, 0);
		PlayerEntityHandles.Insert(Agent->GetEntityHandle(), 0);
	}
	else
	{
		REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Entity is pending creation for pawn{0}"), Pawn);
	}
}

bool URemMassGameStateSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	return CastChecked<UWorld>(Outer)->IsGameWorld();
}
