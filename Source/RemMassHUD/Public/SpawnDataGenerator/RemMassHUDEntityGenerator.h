// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemMassHUDEntitySpawnData.h"
#include "SpawnDataGenerator/RemMassEntitySpawnDataRegenerator.h"

#include "RemMassHUDEntityGenerator.generated.h"

UCLASS(BlueprintType)
class REMMASSHUD_API URemMassHUDEntityGenerator : public URemMassEntitySpawnDataRegenerator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Tags", meta = (Categories = "HUD"))
	FGameplayTagContainer HUDTags;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	FGameplayTagContainer ReceivedHUDTags;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	FRemMassHUDEntitySpawnDataContainer SpawnDataContainer;

	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	bool bHUDTagsAllReceived;
	
protected:
	virtual bool CanGenerate() const override;
	virtual void GenerateInternal() const override;
	virtual void CleanUp() override;
	
public:
	void AddSpawnData(const FGameplayTag& WidgetTag, TConstArrayView<FRemMassHUDBindingFragment> SpawnData);
};
