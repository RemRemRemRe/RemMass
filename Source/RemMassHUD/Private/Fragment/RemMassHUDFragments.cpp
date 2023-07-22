// Copyright RemRemRemRe, All Rights Reserved.


#include "Fragment/RemMassHUDFragments.h"

#include "Macro/RemAssertionMacros.h"
#include "Task/RemMassHUDTask.h"

void FRemMassHUDBindingFragment::UpdateWidget(const TConstArrayView<FConstStructView> StructViews) const
{
	const auto* TaskPtr = Task.GetPtr<FRemMassHUDTask>();

	RemCheckVariable(TaskPtr, return;);

	UWidget* OwningWidget = Widget.Get();
	RemCheckVariable(OwningWidget, return;);
	
	RemCheckCondition(StructViews.Num() > 0, return;);
	
	TaskPtr->DoWork(*OwningWidget, StructViews);
}

bool FRemMassHUDBindingFragment::IsValid() const
{
	RemCheckCondition(FragmentTypes.Num() > 0, return false, REM_NO_LOG_AND_ASSERTION);
	RemCheckVariable(Task, return false, REM_NO_LOG_AND_ASSERTION);
	
	return Widget.Get() != nullptr;
}
