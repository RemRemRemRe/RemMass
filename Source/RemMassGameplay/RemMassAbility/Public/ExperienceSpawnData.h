// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassCommonFragments.h"

#include "ExperienceSpawnData.generated.h"

struct FRemMassExperienceTypeFragment;

USTRUCT()
struct REMMASSABILITY_API FRemExperienceSpawnDataContainer
{
	GENERATED_BODY()

	TConstArrayView<FRemMassExperienceTypeFragment> ExpTypeData;

	UPROPERTY(EditAnywhere)
	TArray<FTransformFragment> TransformData;
};
