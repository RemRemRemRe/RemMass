// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemMetaTags.h"
#include "Macro/RemGenerateMembersMacro.h"

#include "RemMassAbilityTags.generated.h"

UCLASS(config = RemMassAbilityTags)
class REMMASSABILITY_API URemMassAbilityTags : public URemMetaTags
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category = "Attribute", meta = (GameplayTagFilter = "Exp"))
	FGameplayTag RequiredExpToLevelUpTag;

	UPROPERTY(Config, EditAnywhere, Category = "Attribute", meta = (GameplayTagFilter = "Exp"))
	FGameplayTag ExpGainPerLevelTag;

	UPROPERTY(Config, EditAnywhere, Category = "Spawner", meta = (GameplayTagFilter = "MassSpawner"))
	FGameplayTag ExpMassSpawnerTag;

	UPROPERTY(Config, EditAnywhere, Category = "Spawner", meta = (GameplayTagFilter = "MassSpawner"))
	FGameplayTag ProjectileMassSpawnerTag;

public:
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(RequiredExpToLevelUpTag);
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(ExpGainPerLevelTag);
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(ExpMassSpawnerTag);
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(ProjectileMassSpawnerTag);
};
