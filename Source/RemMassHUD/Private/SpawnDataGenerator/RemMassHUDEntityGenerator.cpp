// Copyright RemRemRemRe, All Rights Reserved.


#include "SpawnDataGenerator/RemMassHUDEntityGenerator.h"

#include "MassEntityConfigAsset.h"
#include "Fragment/RemMassHUDFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "Processor/RemMassHUDInitializerProcessor.h"

bool URemMassHUDEntityGenerator::CanGenerate() const
{
	return bHUDTagsAllReceived && Super::CanGenerate();
}

void URemMassHUDEntityGenerator::GenerateInternal() const
{
	RemCheckVariable(SavedQueryOwner, return;);

	for (int32 Index = 0; Index < SavedEntityTypes.Num(); ++Index)
	{
		const auto& SavedEntityType = SavedEntityTypes[Index];
		const auto* EntityConfig = SavedEntityType.EntityConfig.Get();
		RemCheckCondition(EntityConfig, continue;);

		if (const auto& Template = EntityConfig->GetOrCreateEntityTemplate(*SavedQueryOwner->GetWorld());
			!Template.HasFragment<FRemMassHUDBindingFragment>())
		{
			continue;
		}

		FMassEntitySpawnDataGeneratorResult Result
		{
			.SpawnData = {FInstancedStruct::Make(SpawnDataContainer)},
			.SpawnDataProcessor = URemMassHUDInitializerProcessor::StaticClass(),
			.EntityConfigIndex = Index,
			.NumEntities = SpawnDataContainer.SpawnData.Num(),
		};
		
		SavedFinishedGeneratingSpawnPointsDelegate.Execute({Result});
		return;
	}
}

void URemMassHUDEntityGenerator::AddSpawnData(const FGameplayTag& WidgetTag, TConstArrayView<FRemMassHUDBindingFragment> SpawnData)
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
