// Copyright RemRemRemRe, All Rights Reserved.


#include "SpawnDataGenerator/RemMassHUDEntityGenerator.h"

#include "MassEntityConfigAsset.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"

void URemMassHUDEntityGenerator::Generate(UObject& QueryOwner, const TConstArrayView<FMassSpawnedEntityType> EntityTypes,
	const int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const
{
	RemCheckCondition(Count > 0, return;);
	
	ThisClass* MutableThis = const_cast<ThisClass*>(this);
	
	MutableThis->SavedQueryOwner = &QueryOwner;
	MutableThis->SavedEntityTypes = EntityTypes;
	MutableThis->SavedCount = Count;
	MutableThis->SavedFinishedGeneratingSpawnPointsDelegate = FinishedGeneratingSpawnPointsDelegate;

	MutableThis->bCachedData = true;
	
	if (CanGenerate())
	{
		MutableThis->GenerateInternal();
	}
}

bool URemMassHUDEntityGenerator::CanGenerate() const
{
	return bCachedData && bHUDTagsAllReceived;
}

void URemMassHUDEntityGenerator::GenerateInternal() const
{
	RemCheckVariable(SavedQueryOwner.IsValid(), return;);

	for (int32 Index = 0; Index < SavedEntityTypes.Num(); ++Index)
	{
		const auto & SavedEntityType = SavedEntityTypes[Index];
		const auto* EntityConfig = SavedEntityType.GetEntityConfig();
		RemCheckCondition(EntityConfig, continue;);

		if (const auto& Template = EntityConfig->GetOrCreateEntityTemplate(*SavedQueryOwner->GetWorld());
			!Template.HasFragment<FRemMassHUDTextBlockBindingFragment>())
		{
			continue;
		}

		FMassEntitySpawnDataGeneratorResult Result
		{
			.SpawnData = {FInstancedStruct::Make(SpawnDataContainer)},
			.SpawnDataProcessor = {},
			.EntityConfigIndex = Index,
			.NumEntities = SavedCount,
		};
		
		SavedFinishedGeneratingSpawnPointsDelegate.Execute({Result});
		return;
	}
}

void URemMassHUDEntityGenerator::AddSpawnData(const FGameplayTag& WidgetTag,
	TConstArrayView<FRemMassHUDTextBlockBindingFragment> SpawnData)
{
	ReceivedHUDTags.AddTag(WidgetTag);
	SpawnDataContainer.SpawnData.Append(SpawnData);

	if (ReceivedHUDTags == HUDTags)
	{
		bHUDTagsAllReceived = true;
		
		if (CanGenerate())
		{
			GenerateInternal();
		}
	}
}
