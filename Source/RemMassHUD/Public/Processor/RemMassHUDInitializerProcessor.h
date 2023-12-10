// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassHUDInitializerProcessor.generated.h"


UCLASS()
class REMMASSHUD_API URemMassHUDInitializerProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassHUDInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
