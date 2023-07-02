// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDEntitySpawnData.generated.h"

struct FRemMassHUDBindingFragment;

USTRUCT(BlueprintType)
struct FRemMassHUDEntitySpawnDataContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FRemMassHUDBindingFragment> SpawnData;
};
