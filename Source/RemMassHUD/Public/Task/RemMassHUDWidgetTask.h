// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDTask.h"
#include "RemMassHUDWidgetTask.generated.h"

struct FInstancedStruct;
class UTextBlock;

USTRUCT(BlueprintType)
struct REMMASSHUD_API FRemMassHUDWidgetTask : public FRemMassHUDTask
{
	GENERATED_BODY()
	
protected:
	~FRemMassHUDWidgetTask() = default;

	virtual void DoWork(UWidget& OwningWidget, const FInstancedStruct& DataBinding) override;
};
