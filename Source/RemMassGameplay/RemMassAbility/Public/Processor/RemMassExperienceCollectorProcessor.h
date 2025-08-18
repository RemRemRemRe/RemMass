// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Processor/RemMassProcessor.h"
#include "RemMassExperienceCollectorProcessor.generated.h"

UCLASS()
class REMMASSABILITY_API URemMassExperienceCollectorProcessor : public URemMassProcessor
{
	GENERATED_BODY()

public:
	URemMassExperienceCollectorProcessor();

protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
