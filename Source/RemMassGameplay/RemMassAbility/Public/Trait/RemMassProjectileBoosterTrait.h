// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassProjectileBoosterTrait.generated.h"


UCLASS()
class REMMASSABILITY_API URemMassProjectileBoosterTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	FRemMassProjectileTriggerInfoFragment ProjectileTrigger;

	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	FRemMassProjectileInfoFragment ProjectileInfo;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	virtual bool ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
