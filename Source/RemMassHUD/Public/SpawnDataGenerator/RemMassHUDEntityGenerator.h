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

	UPROPERTY(EditAnywhere, Category = "Rem|HUD")
	FGameplayTagContainer HUDTags;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Rem|HUD")
	FGameplayTagContainer ReceivedHUDTags;
	
	UPROPERTY(VisibleInstanceOnly, Transient)
	FRemMassHUDEntitySpawnDataContainer SpawnDataContainer;

	UPROPERTY(Transient, Category = "Rem|HUD|State")
	TWeakObjectPtr<UObject> SavedQueryOwner;

	UPROPERTY(Transient, Category = "Rem|HUD|State")
	TConstArrayView<FMassSpawnedEntityType> SavedEntityTypes;
	
	UPROPERTY(Transient, Category = "Rem|HUD|State")
	int32 SavedCount;
	
	UPROPERTY(Transient, Category = "Rem|HUD|State")
	FFinishedGeneratingSpawnDataSignature SavedFinishedGeneratingSpawnPointsDelegate;
	
	UPROPERTY(Transient, Category = "Rem|HUD|State")
	bool bCachedData;

	UPROPERTY(Transient, Category = "Rem|HUD|State")
	bool bHUDTagsAllReceived;
	
protected:
	virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes,
		int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;

	bool CanGenerate() const;

	void GenerateInternal() const;
	
public:
	void AddSpawnData(const FGameplayTag& WidgetTag, TConstArrayView<FRemMassHUDTextBlockBindingFragment> SpawnData);
};
