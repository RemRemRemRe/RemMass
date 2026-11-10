// Copyright RemRemRemRe, All Rights Reserved.

#pragma once
#include "MassStateTreeTypes.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Object/RemEmptyStruct.h"

#include "RemMassAbilityInitializeTreeLeafsTask.generated.h"

USTRUCT()
struct FRemMassAbilityInitializeTreeLeafsTask : public FMassStateTreeTaskBase
{
    GENERATED_BODY()

    using FInstanceDataType = FRemEmptyStruct;

    FRemMassAbilityInitializeTreeLeafsTask();

public:
    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
        const FStateTreeTransitionResult& Transition) const override;
    virtual const UStruct* GetInstanceDataType() const override;

protected:
    static void DeepFirstSearch(const FMassEntityManager& Manager,
        const Rem::Mass::Ability::FTreeNodeEntityArray& Values,
        const Rem::Mass::Ability::FTreeNodeNumType Num, const FRemMassProjectileTriggerInfoFragment& TriggerInfo,
        const FRemMassProjectileInfoFragment Info);
};

inline const UStruct* FRemMassAbilityInitializeTreeLeafsTask::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
