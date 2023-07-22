// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Processor/RemMassObserverProcessor.h"
#include "RemMassOnPlayerAddedProcessor.generated.h"

/**
 * 
 */
UCLASS()
class REMMASS_API URemMassOnPlayerAddedProcessor : public URemMassObserverProcessor
{
	GENERATED_BODY()

public:
	URemMassOnPlayerAddedProcessor();

protected:
	virtual void Register() override;
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
