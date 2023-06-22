// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "RemMassHealthTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassHealthTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Health", meta = (ShowOnlyInnerProperties))
	FRemMassHealthFragment Health;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
