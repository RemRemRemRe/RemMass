// Copyright RemRemRemRe, All Rights Reserved.

#pragma once
#include "MassEntityTypes.h"

#include "RemMassInventoryInitialized.generated.h"

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryInitialized
{
	GENERATED_BODY()

	FMassEntityManager* Manager;
	
	UPROPERTY(EditAnywhere)
	FMassEntityHandle OwnerEntity;
	
	TMap<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>>* InitialItemEntities;
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemsInitialized
{
	GENERATED_BODY()

	FMassEntityManager* Manager;
	
	UPROPERTY(EditAnywhere)
	FMassEntityHandle OwnerEntity;
	
	TPair<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>>* Entities;
};
