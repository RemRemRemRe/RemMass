// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassMovementProcessor.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSMOVEMENT_API URemMassMovementProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassMovementProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
