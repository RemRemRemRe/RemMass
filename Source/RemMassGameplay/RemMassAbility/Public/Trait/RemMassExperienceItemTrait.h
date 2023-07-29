// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassExperienceItemTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassExperienceItemTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	virtual void ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
