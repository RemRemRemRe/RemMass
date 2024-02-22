// Copyright RemRemRemRe, All Rights Reserved.


#include "SpawnDataGenerator/RemMassProjectileRegenerator.h"

#include "MassEntityConfigAsset.h"
#include "Macro/RemAssertionMacros.h"
#include "Processor/RemMassProjectileInitializerProcessor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassProjectileRegenerator)

void URemMassProjectileRegenerator::GenerateInternal() const
{
	RemCheckVariable(SavedQueryOwner, return;);

	TArray<FMassEntitySpawnDataGeneratorResult> Results;
	
	for (int32 ContainerIndex = 0; ContainerIndex < SpawnDataContainer.SpawnData.Num(); ++ContainerIndex)
	{
		const auto* ConfigAsset = SpawnDataContainer.ConfigAssets[ContainerIndex].Get();
		RemCheckVariable(ConfigAsset, continue;);
		
		for (int32 Index = 0; Index < SavedEntityTypes.Num(); ++Index)
		{
			const auto& SavedEntityType = SavedEntityTypes[Index];
			const auto* EntityConfig = SavedEntityType.EntityConfig.Get();
			RemCheckCondition(EntityConfig, continue;);

			if (ConfigAsset != EntityConfig)
			{
				continue;
			}

			FMassEntitySpawnDataGeneratorResult Result
			{
				.SpawnData = {FInstancedStruct::Make(SpawnDataContainer.SpawnData[ContainerIndex])},
				.SpawnDataProcessor = URemMassProjectileInitializerProcessor::StaticClass(),
				.EntityConfigIndex = Index,
				.NumEntities = SpawnDataContainer.SpawnData[ContainerIndex].Locations.Num(),
			};

			Results.Add(std::move(Result));
			break;
		}
	}

	RemCheckCondition(Results.Num() > 0, return;, REM_NO_LOG_BUT_ENSURE);
	SavedFinishedGeneratingSpawnPointsDelegate.Execute(Results);
}

void URemMassProjectileRegenerator::CleanUp()
{
	SpawnDataContainer = {};
}

void URemMassProjectileRegenerator::AddSpawnData(const FRemProjectileSpawnDataContainer& SpawnData)
{
	SpawnDataContainer.SpawnData.Append(SpawnData.SpawnData);
	SpawnDataContainer.ConfigAssets.Append(SpawnData.ConfigAssets);
}
