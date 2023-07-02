// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessorBase.h"
#include "RemMassDamageProcessor.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSABILITY_API URemMassDamageProcessor : public URemMassProcessorBase
{
	GENERATED_BODY()

public:
	URemMassDamageProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
