// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassExperienceTrait.generated.h"


UCLASS()
class REMMASSABILITY_API URemMassExperienceTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Experience", meta = (ShowOnlyInnerProperties))
	FRemMassExperienceTypeFragment ExperienceType;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
