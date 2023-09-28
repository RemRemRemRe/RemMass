// Copyright RemRemRemRe, All Rights Reserved.

#pragma once
#include "GameplayTagContainer.h"

#include "RemMassTagCountPair.generated.h"

USTRUCT(BlueprintType)
struct FRemMassTagCountPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;
	
	UPROPERTY(EditAnywhere)
	int32 Count{};
};
