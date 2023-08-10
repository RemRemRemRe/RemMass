// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassAbilityFragments.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassProjectileSpawnerTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassProjectileSpawnerTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	float SpawnInterval{1.0f};
	
	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	float InitialSpeed{500.0f};
	
	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	TObjectPtr<UMassEntityConfigAsset> ProjectileConfigAsset;
	
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
