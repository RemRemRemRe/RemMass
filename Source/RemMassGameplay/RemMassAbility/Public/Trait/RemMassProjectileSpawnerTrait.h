// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassProjectileBoosterTrait.h"
#include "RemMassProjectileSpawnerTrait.generated.h"

class UMassEntityConfigAsset;

UCLASS()
class REMMASSABILITY_API URemMassProjectileSpawnerTrait : public URemMassProjectileBoosterTrait
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile Spawner")
	TObjectPtr<UMassEntityConfigAsset> ProjectileConfigAsset;
	
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
