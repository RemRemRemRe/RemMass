// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "ExperienceSpawnData.generated.h"

struct FTransformFragment;
struct FRemMassExperienceTypeFragment;

USTRUCT()
struct REMMASSABILITY_API FRemExperienceSpawnDataContainer
{
	GENERATED_BODY()

	TConstArrayView<FRemMassExperienceTypeFragment> ExpTypeData;

	TArray<FTransformFragment> TransformData;
};
