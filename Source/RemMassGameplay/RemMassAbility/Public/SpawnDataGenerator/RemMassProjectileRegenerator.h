// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "ProjectileSpawnData.h"
#include "SpawnDataGenerator/RemMassEntitySpawnDataRegenerator.h"
#include "RemMassProjectileRegenerator.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassProjectileRegenerator : public URemMassEntitySpawnDataRegenerator
{
	GENERATED_BODY()
	
	UPROPERTY(Transient, VisibleInstanceOnly)
	FRemProjectileSpawnDataContainer SpawnDataContainer;

protected:
	virtual void GenerateInternal() const override;
	virtual void CleanUp() override;

public:
	void AddSpawnData(const FRemProjectileSpawnDataContainer& SpawnData);
};
