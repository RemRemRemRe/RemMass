// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessorBase.h"
#include "RemMassMovementProcessor.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSMOVEMENT_API URemMassMovementProcessor : public URemMassProcessorBase
{
	GENERATED_BODY()

public:
	URemMassMovementProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
