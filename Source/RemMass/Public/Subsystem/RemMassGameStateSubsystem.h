// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "MassEntityTypes.h"
#include "RemMassGameStateSubsystem.generated.h"

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
	TArray<const APawn*> PlayerActors;

public:
	auto GetLocalPlayerEntityHandle() const -> FMassEntityHandle;
	auto GetLocalPlayerPawn() const -> const APawn*;

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|GameState")
	auto AddPlayerEntity(const APawn* PlayerPawn) -> void;
	
	virtual auto Initialize(FSubsystemCollectionBase& Collection) -> void override;
};
