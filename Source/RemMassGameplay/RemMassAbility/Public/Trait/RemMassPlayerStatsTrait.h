// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassPlayerStatsTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassPlayerStatsTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Stats", meta = (ShowOnlyInnerProperties))
	FRemMassLevelCurveTableFragment CurveTable;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
