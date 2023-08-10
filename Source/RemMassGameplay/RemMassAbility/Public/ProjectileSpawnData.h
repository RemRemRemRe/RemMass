// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "ProjectileSpawnData.generated.h"

class UMassEntityConfigAsset;

USTRUCT()
struct FRemProjectileSpawnData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FVector> Locations;

	UPROPERTY(EditAnywhere)
	TArray<FQuat> Rotations;

	UPROPERTY(EditAnywhere)
	TArray<FVector> InitialVelocities;
};

USTRUCT()
struct FRemProjectileSpawnDataContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FRemProjectileSpawnData> SpawnData;

	UPROPERTY(EditAnywhere)
	TArray<TWeakObjectPtr<UMassEntityConfigAsset>> ConfigAssets;

	void Reserve(uint32 Num);

	int32 FindOrAdd(TWeakObjectPtr<UMassEntityConfigAsset> Asset);

};

inline void FRemProjectileSpawnDataContainer::Reserve(const uint32 Num)
{
	SpawnData.Reserve(Num);
	ConfigAssets.Reserve(Num);
}

inline int32 FRemProjectileSpawnDataContainer::FindOrAdd(const TWeakObjectPtr<UMassEntityConfigAsset> Asset)
{
	if (const int32 Index = ConfigAssets.Find(Asset);
		Index != -1)
	{
		return Index;
	}
	
	SpawnData.AddDefaulted();
	return  ConfigAssets.Add(Asset);
}
