// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "ExperienceSpawnData.h"
#include "SpawnDataGenerator/RemMassEntitySpawnDataRegenerator.h"
#include "RemMassExperienceRegenerator.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassExperienceRegenerator : public URemMassEntitySpawnDataRegenerator
{
	GENERATED_BODY()

	UPROPERTY(Transient, VisibleInstanceOnly)
	FRemExperienceSpawnDataContainer SpawnDataContainer;

protected:
	virtual bool CanGenerate() const override;
	virtual void GenerateInternal() const override;
	virtual void CleanUp() override;

public:
	void AddSpawnData(const FRemExperienceSpawnDataContainer& SpawnData);
};
