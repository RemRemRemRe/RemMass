// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDTask.h"
#include "RemMassHUDWidgetTask.generated.h"

USTRUCT(BlueprintType)
struct REMMASSHUD_API FRemMassHUDWidgetTask : public FRemMassHUDTask
{
	GENERATED_BODY()

	virtual ~FRemMassHUDWidgetTask() override = default;

protected:
	virtual void DoWork(UWidget& OwningWidget, TConstArrayView<FConstStructView> DataBindings) const override;
};
