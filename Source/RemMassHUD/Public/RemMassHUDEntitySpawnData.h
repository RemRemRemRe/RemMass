// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDEntitySpawnData.generated.h"

struct FRemMassHUDTextBlockBindingFragment;

USTRUCT(BlueprintType)
struct FRemMassHUDEntitySpawnDataContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FRemMassHUDTextBlockBindingFragment> SpawnData;
};
