// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemWidgetComponentBase.h"
#include "Fragment/RemMassHUDFragments.h"
#include "RemMassHUDBinder.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSHUD_API URemMassHUDBinder : public URemWidgetComponentBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Binding", meta = (Categories = "HUD"))
	FGameplayTag WidgetTag;
	
	UPROPERTY(EditAnywhere, Category = "Binding")
	TArray<FRemMassHUDBindingFragment> Bindings;

protected:
	virtual void BeginPlay() override;
};
