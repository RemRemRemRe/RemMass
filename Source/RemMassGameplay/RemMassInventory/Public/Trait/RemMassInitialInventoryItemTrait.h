// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassInventoryTagCountPair.h"
#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassInitialInventoryItemTrait.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSINVENTORY_API URemMassInitialInventoryItemTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item", meta = (TitleProperty = "Tag", Categories = "InventoryItem"))
	TArray<FRemMassInventoryTagCountPairContainer> InitialItems;
	
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
