// Copyright RemRemRemRe, All Rights Reserved.


#include "SpawnDataGenerator/RemMassExperienceRegenerator.h"

#include "MassEntityConfigAsset.h"
#include "Macro/RemAssertionMacros.h"
#include "Processor/RemMassExpInitializerProcessor.h"

bool URemMassExperienceRegenerator::CanGenerate() const
{
	return !SpawnDataContainer.ExpTypeData.IsEmpty() && Super::CanGenerate();
}

void URemMassExperienceRegenerator::GenerateInternal() const
{
	RemCheckVariable(SavedQueryOwner, return;);

	for (int32 Index = 0; Index < SavedEntityTypes.Num(); ++Index)
	{
		const auto& SavedEntityType = SavedEntityTypes[Index];
		const auto* EntityConfig = SavedEntityType.EntityConfig.Get();
		RemCheckCondition(EntityConfig, continue;);

		if (const auto& Template = EntityConfig->GetOrCreateEntityTemplate(*SavedQueryOwner->GetWorld());
			!Template.HasFragment<FRemMassExperienceTypeFragment>())
		{
			continue;
		}

		FMassEntitySpawnDataGeneratorResult Result
		{
			.SpawnData = {FInstancedStruct::Make(SpawnDataContainer)},
			.SpawnDataProcessor = URemMassExpInitializerProcessor::StaticClass(),
			.EntityConfigIndex = Index,
			.NumEntities = SpawnDataContainer.ExpTypeData.Num(),
		};
		
		SavedFinishedGeneratingSpawnPointsDelegate.Execute({Result});
		return;
	}
}

void URemMassExperienceRegenerator::CleanUp()
{
	SpawnDataContainer = {};
}

void URemMassExperienceRegenerator::AddSpawnData(const FRemExperienceSpawnDataContainer& SpawnData)
{
	SpawnDataContainer = SpawnData;
}
