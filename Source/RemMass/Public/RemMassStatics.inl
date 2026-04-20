// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityTypes.h"
#include "MassEntitySubsystem.h"
#include "RemMassSpawner.h"
#include "RemMassStatics.h"
#include "Macro/RemAssertionMacros.h"

class UMassEntitySpawnDataGeneratorBase;
class ARemMassSpawner;

namespace Rem::Mass
{
template <std::derived_from<FMassFragment> FragmentType>
FragmentType* GetFragmentDataPtr(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle)
{
    RemCheckVariable(WorldContextObject, return {});
    RemCheckVariable(EntityHandle, return {});

    const auto* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(WorldContextObject->GetWorld());
    RemCheckVariable(EntitySubsystem, return {});

    return EntitySubsystem->GetEntityManager().GetFragmentDataPtr<FragmentType>(EntityHandle);
}

template <std::derived_from<FMassFragment> FragmentType>
decltype(auto) GetFragmentData(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle)
{
    return *GetFragmentDataPtr<FragmentType>(WorldContextObject, EntityHandle);
}

template <std::derived_from<UMassEntitySpawnDataGeneratorBase> TGeneratorType>
TGeneratorType* GetSpawnDataGenerator(const UObject* WorldContextObject, const FGameplayTagQuery& SpawnerQuery)
{
    auto* HUDSpawner = URemMassStatics::GetMassSpawner(WorldContextObject, SpawnerQuery);
    RemCheckVariable(HUDSpawner, return {};);

    return HUDSpawner->GetSpawnDataGenerator<TGeneratorType>();
}

}
