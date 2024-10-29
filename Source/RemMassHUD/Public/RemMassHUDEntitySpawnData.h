// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassHUDFragments.h"

#include "RemMassHUDEntitySpawnData.generated.h"

USTRUCT(BlueprintType)
struct REMMASSHUD_API FRemMassHUDEntitySpawnDataContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FRemMassHUDBindingFragment> SpawnData;
};
