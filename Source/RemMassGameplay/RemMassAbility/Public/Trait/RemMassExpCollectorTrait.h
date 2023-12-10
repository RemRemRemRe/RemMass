// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassExpCollectorTrait.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassExpCollectorTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Experience", meta = (ShowOnlyInnerProperties))
	FRemMassExpCollectRadiusFragment Radius;
	
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
