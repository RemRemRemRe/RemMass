// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemWidgetComponentBase.h"
#include "RemMassHUDFragmentReader.generated.h"

/**
 * 
 */
UCLASS()
class REMMASSHUD_API URemMassHUDFragmentReader : public URemWidgetComponentBase
{
	GENERATED_BODY()

protected:
	virtual bool RequiresTick() const override;
	virtual void Tick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void BeginPlay() override;
};
