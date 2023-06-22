// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassRespawnTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassRespawnTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Respawn", meta = (ShowOnlyInnerProperties))
	FRemMassRespawnRadiusFragment RespawnRadius;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
