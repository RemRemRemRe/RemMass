// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassExpInitializerProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassExpInitializerProcessor : public URemMassProcessor
{
	GENERATED_BODY()
public:
	URemMassExpInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
