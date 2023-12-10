// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassRespawnProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassRespawnProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassRespawnProcessor();
	
protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
