// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemMetaTags.h"
#include "Macro/RemGenerateMembersMacro.h"

#include "RemMassAbilityTags.generated.h"

/**
 * 
 */
UCLASS(config = RemMassAbilityTags)
class REMMASSABILITY_API URemMassAbilityTags : public URemMetaTags
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category = "Attribute", meta = (Categories = "Exp"))
	FGameplayTag RequiredExpToLevelUpTag;

	UPROPERTY(Config, EditAnywhere, Category = "Attribute", meta = (Categories = "Exp"))
	FGameplayTag ExpGainPerLevelTag;

public:
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE(RequiredExpToLevelUpTag, FGameplayTag, &RequiredExpToLevelUpTag);
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE(ExpGainPerLevelTag, FGameplayTag, &ExpGainPerLevelTag);
};
