// Copyright RemRemRemRe, All Rights Reserved.


#include "Fragment/RemMassHUDFragments.h"

#include "Components/Widget.h"
#include "Macro/RemAssertionMacros.h"
#include "Task/RemMassHUDTask.h"

void FRemMassHUDBindingFragment::UpdateWidget(const FConstStructView StructView) const
{
	const auto* TaskPtr = Task.GetPtr<FRemMassHUDTask>();

	RemCheckVariable(TaskPtr, return;);

	UWidget* OwningWidget = Widget.Get();
	RemCheckVariable(OwningWidget, return;);
	
	TaskPtr->DoWork(*OwningWidget, StructView);
}
