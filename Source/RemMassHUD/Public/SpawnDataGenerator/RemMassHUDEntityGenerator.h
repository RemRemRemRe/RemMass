// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RemMassHUDEntitySpawnData.h"
#include "SpawnDataGenerator/RemMassEntitySpawnDataGeneratorBase.h"
#include "RemMassHUDEntityGenerator.generated.h"

UCLASS(BlueprintType)
class REMMASSHUD_API URemMassHUDEntityGenerator : public URemMassEntitySpawnDataGeneratorBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Tags", meta = (Categories = "HUD"))
	FGameplayTagContainer HUDTags;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	FGameplayTagContainer ReceivedHUDTags;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	FRemMassHUDEntitySpawnDataContainer SpawnDataContainer;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	TWeakObjectPtr<UObject> SavedQueryOwner;

	TConstArrayView<FMassSpawnedEntityType> SavedEntityTypes;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	int32 SavedCount;
	
	FFinishedGeneratingSpawnDataSignature SavedFinishedGeneratingSpawnPointsDelegate;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	bool bCachedData;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	bool bHUDTagsAllReceived;
	
protected:
	virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes,
		int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;

	bool CanGenerate() const;

	void GenerateInternal() const;
	
public:
	void AddSpawnData(const FGameplayTag& WidgetTag, TConstArrayView<FRemMassHUDBindingFragment> SpawnData);
};
