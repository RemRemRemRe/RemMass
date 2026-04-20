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

    bool IsLocalPlayerPawnValid() const;
    bool IsLocalPlayerEntityValid() const;
    FMassEntityHandle GetLocalPlayerEntity() const;
    const APawn* GetLocalPlayerPawn() const;

    TConstArrayView<FMassEntityHandle> GetPlayerEntityView() const;
    TConstArrayView<APawn*> GetPlayerActorView() const;

    FRemMassNearbyMonsterEntityData GetNearbyMonsterEntityData(FMassEntityHandle PlayerEntityHandle) const;
    FVector GetNearestMonsterDirection(FMassEntityHandle PlayerEntityHandle) const;
    double GetNearestMonsterDistanceSquared(FMassEntityHandle PlayerEntityHandle) const;

    ARemMassSpawner* GetMassSpawner(const FGameplayTagQuery& SpawnerQuery) const;
    void RegisterMassSpawner(ARemMassSpawner& MassSpawner);

    UFUNCTION(BlueprintCallable, Category = "Rem|Mass|GameState")
    void AddPlayerEntity(APawn* PlayerPawn);

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    REM_DEFINE_GETTERS_RETURN_REFERENCE_SIMPLE(NearbyMonsterEntityDataContainer)
};

template <typename T>
struct TMassExternalSubsystemTraits;

template <>
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
