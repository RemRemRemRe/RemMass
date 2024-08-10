// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassHUDLog.h"
#include "Macro/RemCoreMiscDefines.h"
#include "RemMassHUDTask.generated.h"

struct FConstStructView;
class UWidget;

USTRUCT()
struct FRemMassHUDTask
{
	GENERATED_BODY()

	virtual ~FRemMassHUDTask() = default;

	virtual void DoWork(UWidget& OwningWidget, TConstArrayView<FConstStructView> DataBindings) const REM_VIRTUAL_WARN(LogRemMassHUD);
};
