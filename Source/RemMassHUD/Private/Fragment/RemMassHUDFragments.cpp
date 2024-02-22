// Copyright RemRemRemRe, All Rights Reserved.


#include "Fragment/RemMassHUDFragments.h"

#include "Macro/RemAssertionMacros.h"
#include "Task/RemMassHUDTask.h"
#include "Components/Widget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDFragments)

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
	RemCheckCondition(FragmentTypes.Num() > 0, return false, REM_NO_LOG_BUT_ENSURE);
	RemCheckVariable(Task, return false, REM_NO_LOG_BUT_ENSURE);
	
	return Widget.Get() != nullptr;
}
