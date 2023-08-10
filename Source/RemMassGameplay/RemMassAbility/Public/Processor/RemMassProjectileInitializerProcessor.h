// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassProjectileInitializerProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassProjectileInitializerProcessor : public URemMassProcessor
{
	GENERATED_BODY()
	
public:
	URemMassProjectileInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
