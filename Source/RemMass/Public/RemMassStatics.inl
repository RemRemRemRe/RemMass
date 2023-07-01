// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityTypes.h"
#include "MassEntitySubsystem.h"
#include "Macro/RemAssertionMacros.h"

namespace Rem::Mass
{
	template <typename FragmentType>
	requires std::is_base_of_v<FMassFragment, FragmentType>
	auto GetFragmentDataPtr(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle) -> decltype(auto)
	{
		RemCheckVariable(WorldContextObject, return {});
		RemCheckVariable(EntityHandle, return {});
	
		// Fetch NetID if it exist
		const UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(WorldContextObject->GetWorld());
		RemCheckVariable(EntitySubsystem, return {});

		return EntitySubsystem->GetEntityManager().GetFragmentDataPtr<FragmentType>(EntityHandle);
	}

	template <typename FragmentType>
	auto GetFragmentData(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle) -> decltype(auto)
	{
		return *GetFragmentDataPtr<FragmentType>(WorldContextObject, EntityHandle);
	}

}
