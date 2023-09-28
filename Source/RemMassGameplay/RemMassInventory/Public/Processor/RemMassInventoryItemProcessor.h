// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassInventoryItemProcessor.generated.h"

UCLASS()
class REMMASSINVENTORY_API URemMassInventoryItemProcessor : public URemMassProcessor
{
	GENERATED_BODY()
	
public:
	URemMassInventoryItemProcessor();
	
protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
