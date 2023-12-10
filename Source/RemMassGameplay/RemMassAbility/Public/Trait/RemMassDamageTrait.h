// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "MassEntityTraitBase.h"
#include "RemMassDamageTrait.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassDamageTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	/**
	 * @brief DamageSource Or DamageTarget
	 */
	UPROPERTY(EditAnywhere, Category = "Damage")
	bool bDamageSource;
	
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (ShowOnlyInnerProperties, EditCondition = "bDamageSource"))
	FRemMassDamageFragment Damage;

	UPROPERTY(EditAnywhere, Category = "Damage", meta = (ShowOnlyInnerProperties, EditCondition = "bDamageSource"))
	FRemMassDamageRadiusFragment DamageRadius;

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
