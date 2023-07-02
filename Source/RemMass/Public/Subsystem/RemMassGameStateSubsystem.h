// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "MassEntityTypes.h"
#include "RemMassGameStateSubsystem.generated.h"

struct FGameplayTagQuery;
class ARemMassSpawner;

DECLARE_LOG_CATEGORY_EXTERN(LogRemMassGameState, Log, All)

/**
 * 
 */
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
	TArray<APawn*> PlayerActors;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Rem|Mass|GameState")
	TArray<ARemMassSpawner*> MassSpawners;
	
	mutable FRWLock Lock;
	
public:
	auto GetLocalPlayerEntity() const -> FMassEntityHandle;
	auto GetLocalPlayerPawn() const -> const APawn*;

	auto GetPlayerEntityView() const -> TConstArrayView<FMassEntityHandle>;
	auto GetPlayerActorView() const -> TConstArrayView<APawn*>;

	auto GetMassSpawner(const FGameplayTagQuery& SpawnerQuery) const -> ARemMassSpawner*;
	auto RegisterMassSpawner(ARemMassSpawner& MassSpawner) -> void;

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|GameState")
	void AddPlayerEntity(APawn* PlayerPawn);
	
	virtual auto Initialize(FSubsystemCollectionBase& Collection) -> void override;
	virtual auto ShouldCreateSubsystem(UObject* Outer) const -> bool override;
};

template<>
struct TMassExternalSubsystemTraits<URemMassGameStateSubsystem> final
{
	enum
	{
		GameThreadOnly = false
	};
};
