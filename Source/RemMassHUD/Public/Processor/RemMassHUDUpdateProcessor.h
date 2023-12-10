// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassHUDUpdateProcessor.generated.h"


UCLASS()
class REMMASSHUD_API URemMassHUDUpdateProcessor : public URemMassProcessor
{
	GENERATED_BODY()
	
public:
	URemMassHUDUpdateProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
