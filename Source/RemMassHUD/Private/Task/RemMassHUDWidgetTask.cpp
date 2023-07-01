// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassHUDWidgetTask.h"

#include "Components/Widget.h"
#include "Macro/RemAssertionMacros.h"

void FRemMassHUDWidgetTask::DoWork(UWidget& OwningWidget, const FInstancedStruct& DataBinding)
{
	RemCheckCondition(OwningWidget.IsA<UTextBlock>(), return;);

	auto 
}
