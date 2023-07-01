// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassEntityTraitBase.h"
#include "GameplayTagContainer.h"
#include "RemMassEntityMetaTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASS_API URemMassEntityMetaTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Trait Meta Data")
	FGameplayTagContainer MetaTags;
};
