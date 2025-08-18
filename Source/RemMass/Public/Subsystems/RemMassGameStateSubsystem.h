// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "MassEntityTypes.h"
#include "Macro/RemGenerateMembersMacro.h"
#include "RemMassGameStateSubsystem.generated.h"

struct FMassEntityHandle;
class UMassEntitySubsystem;
struct FGameplayTagQuery;
class ARemMassSpawner;

DECLARE_LOG_CATEGORY_EXTERN(LogRemMassGameState, Log, All)

USTRUCT()
struct FRemMassNearbyMonsterEntityData
{
	GENERATED_BODY()

	TArray<FMassEntityHandle> NearbyMonsterHandles;

	UPROPERTY(EditAnywhere)
	TArray<double> NearbyMonsterDistancesSquared;

	UPROPERTY(EditAnywhere)
	TArray<FVector> NearbyMonsterDirections;

	void RemoveAt(int32 Index);
};

USTRUCT()
struct FRemMassNearbyMonsterDataContainer
{
	GENERATED_BODY()

	TArray<FRemMassNearbyMonsterEntityData> NearbyMonsterEntityData;
};

UCLASS()
class REMMASS_API URemMassGameStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	/**
	 * @brief Local player entity handle will be placed at index 0
	 */
	TArray<FMassEntityHandle> PlayerEntityHandles;

	/**
	 * @brief Local player actor will be placed at index 0
	 */
	UPROPERTY(VisibleInstanceOnly, Category = "Rem|Mass|GameState")
	TArray<APawn*> PlayerPawns;

	UPROPERTY(VisibleInstanceOnly, Category = "Rem|Mass|GameState")
	FRemMassNearbyMonsterDataContainer NearbyMonsterEntityDataContainer;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Rem|Mass|GameState")
	TArray<ARemMassSpawner*> MassSpawners;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Rem|Mass|GameState")
	UMassEntitySubsystem* EntitySubsystem;

public:
	mutable FRWLock PlayerEntityLock;
	mutable FRWLock NearbyMonsterEntityLock;
	mutable FRWLock MassSpawnerLock;

public:
	auto IsLocalPlayerPawnValid() const -> bool;
	auto IsLocalPlayerEntityValid() const -> bool;
	auto GetLocalPlayerEntity() const -> FMassEntityHandle;
	auto GetLocalPlayerPawn() const -> const APawn*;

	auto GetPlayerEntityView() const -> TConstArrayView<FMassEntityHandle>;
	auto GetPlayerActorView() const -> TConstArrayView<APawn*>;

	auto GetNearbyMonsterEntityData(FMassEntityHandle PlayerEntityHandle) const -> FRemMassNearbyMonsterEntityData;
	auto GetNearestMonsterDirection(FMassEntityHandle PlayerEntityHandle) const -> FVector;
	auto GetNearestMonsterDistanceSquared(FMassEntityHandle PlayerEntityHandle) const -> double;

	auto GetMassSpawner(const FGameplayTagQuery& SpawnerQuery) const -> ARemMassSpawner*;
	auto RegisterMassSpawner(ARemMassSpawner& MassSpawner) -> void;

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|GameState")
	void AddPlayerEntity(APawn* PlayerPawn);

	virtual auto Initialize(FSubsystemCollectionBase& Collection) -> void override;
	virtual auto ShouldCreateSubsystem(UObject* Outer) const -> bool override;

	REM_DEFINE_GETTERS_RETURN_REFERENCE_SIMPLE(NearbyMonsterEntityDataContainer)
};

template <typename T>
struct TMassExternalSubsystemTraits;

template<>
struct TMassExternalSubsystemTraits<URemMassGameStateSubsystem> final
{
	enum
	{
		GameThreadOnly = false
	};
};

inline void FRemMassNearbyMonsterEntityData::RemoveAt(const int32 Index)
{
	NearbyMonsterHandles.RemoveAt(Index);
	NearbyMonsterDistancesSquared.RemoveAt(Index);
	NearbyMonsterDirections.RemoveAt(Index);
}
