// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassProjectileSpawnerProcessor.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassProjectileSpawnerProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassProjectileSpawnerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
