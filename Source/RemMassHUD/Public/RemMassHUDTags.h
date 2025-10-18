// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemMetaTags.h"
#include "Macro/RemGenerateMembersMacro.h"

#include "RemMassHUDTags.generated.h"


UCLASS(Config = RemMassHUDTags)
class REMMASSHUD_API URemMassHUDTags : public URemMetaTags
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category = "Spawner", meta = (GameplayTagFilter = "MassSpawner"))
	FGameplayTag HUDMassSpawnerTag;

public:
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(HUDMassSpawnerTag)
};
