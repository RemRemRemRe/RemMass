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
	auto GetFragmentDataPtr(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle) -> FragmentType*
	{
		RemCheckVariable(WorldContextObject, return {});
		RemCheckVariable(EntityHandle, return {});

		const auto* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(WorldContextObject->GetWorld());
		RemCheckVariable(EntitySubsystem, return {});

		return EntitySubsystem->GetEntityManager().GetFragmentDataPtr<FragmentType>(EntityHandle);
	}

	template <std::derived_from<FMassFragment> FragmentType>
	auto GetFragmentData(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle) -> decltype(auto)
	{
		return *GetFragmentDataPtr<FragmentType>(WorldContextObject, EntityHandle);
	}

	template<std::derived_from<UMassEntitySpawnDataGeneratorBase> TGeneratorType>
	auto GetSpawnDataGenerator(const UObject* WorldContextObject, const FGameplayTagQuery& SpawnerQuery) -> TGeneratorType*
	{
		auto* HUDSpawner = URemMassStatics::GetMassSpawner(WorldContextObject, SpawnerQuery);
		RemCheckVariable(HUDSpawner, return {};);

		return HUDSpawner->GetSpawnDataGenerator<TGeneratorType>();
	}

}
