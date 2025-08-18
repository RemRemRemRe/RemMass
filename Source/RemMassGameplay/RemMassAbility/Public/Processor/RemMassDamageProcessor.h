// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassDamageProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassDamageProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassDamageProcessor();

protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery DamageSourceEntityQuery;
	FMassEntityQuery DamageTargetEntityQuery;
};
