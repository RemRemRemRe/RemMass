// Copyright RemRemRemRe, All Rights Reserved.


#include "SpawnDataGenerator/RemMassEntitySpawnDataRegenerator.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassEntitySpawnDataRegenerator)

void URemMassEntitySpawnDataRegenerator::Generate(UObject& QueryOwner,
	const TConstArrayView<FMassSpawnedEntityType> EntityTypes, const int32 Count,
	FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const
{
	auto* MutableThis = const_cast<ThisClass*>(this);
	
	Rem::Mass::FScopedEntitySpawnDataRegeneration ScopedGenerate{*MutableThis};
	
	MutableThis->SavedQueryOwner = &QueryOwner;
	MutableThis->SavedEntityTypes = EntityTypes;
	MutableThis->SavedCount = Count;
	MutableThis->SavedFinishedGeneratingSpawnPointsDelegate = FinishedGeneratingSpawnPointsDelegate;

	MutableThis->bCachedData = true;
}

bool URemMassEntitySpawnDataRegenerator::CanGenerate() const
{
	return bCachedData;
}
