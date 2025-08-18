// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassNearbyMonsterDataProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassNearbyMonsterDataProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassNearbyMonsterDataProcessor();

protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
