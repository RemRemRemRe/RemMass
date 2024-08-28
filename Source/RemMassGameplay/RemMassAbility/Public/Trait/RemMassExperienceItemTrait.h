// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassExperienceItemTrait.generated.h"


UCLASS()
class REMMASSABILITY_API URemMassExperienceItemTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;
};
