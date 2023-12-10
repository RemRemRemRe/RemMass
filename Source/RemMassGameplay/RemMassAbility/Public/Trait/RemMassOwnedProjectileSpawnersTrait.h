// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassOwnedProjectileSpawnersTrait.generated.h"

class UMassEntityConfigAsset;

UCLASS()
class REMMASSABILITY_API URemMassOwnedProjectileSpawnersTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Spawner Config")
	TArray<TObjectPtr<UMassEntityConfigAsset>> ProjectileSpawnerConfigs;
	
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
