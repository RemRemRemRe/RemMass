// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityHandle.h"

#include "RemMassInventoryInitialized.generated.h"

class UMassEntityConfigAsset;
struct FMassEntityManager;

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryInitialized
{
	GENERATED_BODY()

	TWeakPtr<FMassEntityManager> Manager;

	UPROPERTY(EditAnywhere)
	FMassEntityHandle OwnerEntity;

	TMap<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>>* InitialItemEntities;
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemsInitialized
{
	GENERATED_BODY()

	TWeakPtr<FMassEntityManager> Manager;

	UPROPERTY(EditAnywhere)
	FMassEntityHandle OwnerEntity;

	TPair<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>>* Entities;
};
