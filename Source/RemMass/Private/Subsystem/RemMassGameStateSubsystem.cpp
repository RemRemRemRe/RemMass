// Copyright RemRemRemRe, All Rights Reserved.


#include "Subsystem/RemMassGameStateSubsystem.h"

#include "MassAgentComponent.h"
#include "MassEntitySubsystem.h"
#include "RemMassSpawner.h"
#include "GameFramework/Pawn.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"
#include "Object/RemObjectStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassGameStateSubsystem)

DEFINE_LOG_CATEGORY(LogRemMassGameState)


auto URemMassGameStateSubsystem::IsLocalPlayerPawnValid() const -> bool
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	if (!PlayerPawns.IsEmpty())
	{
		if (PlayerPawns[0] && PlayerPawns[0]->IsLocallyControlled())
		{
			return true;
		}
	}
	return false;
}

auto URemMassGameStateSubsystem::IsLocalPlayerEntityValid() const -> bool
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	if (IsValid(EntitySubsystem) && !PlayerEntityHandles.IsEmpty() && PlayerEntityHandles[0].IsValid())
	{
		return EntitySubsystem->GetEntityManager().IsEntityValid(PlayerEntityHandles[0]);
	}
	return false;
}

auto URemMassGameStateSubsystem::GetLocalPlayerEntity() const -> FMassEntityHandle
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	if (IsLocalPlayerEntityValid())
	{
		return PlayerEntityHandles[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::GetLocalPlayerPawn() const -> const APawn*
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	if (IsLocalPlayerPawnValid())
	{
		return PlayerPawns[0];
	}
	return {};
}

auto URemMassGameStateSubsystem::GetPlayerEntityView() const -> TConstArrayView<FMassEntityHandle>
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	return {PlayerEntityHandles};
}

auto URemMassGameStateSubsystem::GetPlayerActorView() const -> TConstArrayView<APawn*>
{
	FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
	
	return {PlayerPawns};
}

auto URemMassGameStateSubsystem::GetNearbyMonsterEntityData(
	const FMassEntityHandle PlayerEntityHandle) const -> FRemMassNearbyMonsterEntityData
{
	int32 Index;

	{
		FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
		Index = PlayerEntityHandles.Find(PlayerEntityHandle);
	}
	
	FRWScopeLock ScopeLock{NearbyMonsterEntityLock, FRWScopeLockType::SLT_ReadOnly};
	if (NearbyMonsterEntityDataContainer.NearbyMonsterEntityData.IsValidIndex(Index))
	{
		return NearbyMonsterEntityDataContainer.NearbyMonsterEntityData[Index];
	}
	
	return {};
}

auto URemMassGameStateSubsystem::GetNearestMonsterDirection(const FMassEntityHandle PlayerEntityHandle) const -> FVector
{
	int32 Index;

	{
		FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
		Index = PlayerEntityHandles.Find(PlayerEntityHandle);
	}
	
	FRWScopeLock ScopeLock{NearbyMonsterEntityLock, FRWScopeLockType::SLT_ReadOnly};
	if (auto& MassNearbyMonsterEntityData = NearbyMonsterEntityDataContainer.NearbyMonsterEntityData;
		MassNearbyMonsterEntityData.IsValidIndex(Index) && !MassNearbyMonsterEntityData[Index].NearbyMonsterDirections.IsEmpty())
	{
		return MassNearbyMonsterEntityData[Index].NearbyMonsterDirections[0];
	}

	RemCheckCondition(false, REM_NO_HANDLING, REM_NO_LOG_BUT_ENSURE);
	return {};
}

auto URemMassGameStateSubsystem::GetNearestMonsterDistanceSquared(const FMassEntityHandle PlayerEntityHandle) const -> double
{
	int32 Index;

	{
		FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_ReadOnly};
		Index = PlayerEntityHandles.Find(PlayerEntityHandle);
	}
	
	FRWScopeLock ScopeLock{NearbyMonsterEntityLock, FRWScopeLockType::SLT_ReadOnly};
	if (auto& MassNearbyMonsterEntityData = NearbyMonsterEntityDataContainer.NearbyMonsterEntityData;
	 MassNearbyMonsterEntityData.IsValidIndex(Index) && !MassNearbyMonsterEntityData[Index].NearbyMonsterDirections.IsEmpty())
	{
		return MassNearbyMonsterEntityData[Index].NearbyMonsterDistancesSquared[0];
	}

	RemCheckCondition(false, REM_NO_HANDLING, REM_NO_LOG_BUT_ENSURE);
	return {};
}

auto URemMassGameStateSubsystem::GetMassSpawner(const FGameplayTagQuery& SpawnerQuery) const -> ARemMassSpawner*
{
	FRWScopeLock ScopeLock{MassSpawnerLock, FRWScopeLockType::SLT_ReadOnly};
	
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
	FRWScopeLock ScopeLock{MassSpawnerLock, FRWScopeLockType::SLT_Write};
	MassSpawners.Add(&MassSpawner);
}

void URemMassGameStateSubsystem::AddPlayerEntity(APawn* PlayerPawn)
{
	RemCheckVariable(PlayerPawn, return;);
	
	const auto* Agent = PlayerPawn->FindComponentByClass<UMassAgentComponent>();
	RemCheckVariable(Agent, return;);
	
	RemCheckCondition(!Agent->IsEntityPendingCreation(), return;);
	
	{
		FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_Write};
		
		if (PlayerPawns.Contains(PlayerPawn))
		{
			REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Pawn{0} already exist"), PlayerPawn);
			return;
		}
		
		if (PlayerPawn->IsLocallyControlled())
		{
			PlayerPawns.Insert(PlayerPawn, 0);
			PlayerEntityHandles.Insert(Agent->GetEntityHandle(), 0);
		}
		else
		{
			PlayerPawns.Add(PlayerPawn);
			PlayerEntityHandles.Add(Agent->GetEntityHandle());
		}
	}
}

auto URemMassGameStateSubsystem::Initialize(FSubsystemCollectionBase& Collection) -> void
{
	Collection.InitializeDependency<UMassEntitySubsystem>();
	
	Super::Initialize(Collection);

	const auto* World = GetWorld();
	RemCheckVariable(World, return;, REM_NO_LOG_BUT_ENSURE);
	
	EntitySubsystem = World->GetSubsystem<UMassEntitySubsystem>();
	RemCheckVariable(EntitySubsystem, REM_NO_HANDLING, REM_NO_LOG_BUT_ENSURE);
	
	auto* Pawn = URemObjectStatics::GetFirstLocalPlayerPawn(World);
	RemCheckVariable(Pawn, return;, REM_NO_LOG_OR_ASSERTION);
	
	const auto* Agent = Pawn->FindComponentByClass<UMassAgentComponent>();
	RemCheckVariable(Agent, return;);

	if (!Agent->IsEntityPendingCreation())
	{
		FRWScopeLock ScopeLock{PlayerEntityLock, FRWScopeLockType::SLT_Write};
		
		PlayerPawns.Insert(Pawn, 0);
		PlayerEntityHandles.Insert(Agent->GetEntityHandle(), 0);
	}
	else
	{
		REM_LOG_FUNCTION(LogRemMassGameState, Log, TEXT("Entity is pending creation for pawn{0}"), Pawn);
	}
}

bool URemMassGameStateSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	RemCheckVariable(Outer, return false);
	
	const auto* World = Outer->GetWorld();
	RemCheckVariable(World, return false);
	
	return World->IsGameWorld() && World->GetSubsystem<UMassEntitySubsystem>() && Super::ShouldCreateSubsystem(Outer);
}
