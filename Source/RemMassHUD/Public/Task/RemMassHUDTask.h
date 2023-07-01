// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDLog.h"
#include "Macro/RemCoreMiscDefines.h"
#include "RemMassHUDTask.generated.h"

struct FInstancedStruct;
class UWidget;

USTRUCT()
struct FRemMassHUDTask
{
	GENERATED_BODY()
	
protected:
	~FRemMassHUDTask() = default;

	virtual void DoWork(UWidget& OwningWidget, const FInstancedStruct& DataBinding) REM_VIRTUAL_WARN(LogRemMassHUD);
};
