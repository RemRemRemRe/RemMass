// Copyright RemRemRemRe, All Rights Reserved.

#pragma once
#include "MassStateTreeTypes.h"

#include "RemMassAbilityInitializeTreeLeafsTask.generated.h"

USTRUCT()
struct FRemMassAbilityInitializeTreeLeafsTask : public FMassStateTreeTaskBase
{
	GENERATED_BODY()

	FRemMassAbilityInitializeTreeLeafsTask();
	
protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
