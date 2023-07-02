// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassHUDWidgetTask.h"

#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"

void FRemMassHUDWidgetTask::DoWork(UWidget& OwningWidget, const FConstStructView DataBinding) const
{
	RemCheckCondition(OwningWidget.IsA<UTextBlock>(), return;);

	auto& Text = static_cast<UTextBlock&>(OwningWidget);

	if (auto* Level = DataBinding.GetPtr<FRemMassLevelFragment>())
	{
		Text.SetText(FText::FromString(FString::Format(TEXTVIEW("{0}").GetData(), {Level->Value})));
	}
	else if (auto* Exp = DataBinding.GetPtr<FRemMassExperienceFragment>())
	{
		Text.SetText(FText::FromString(FString::Format(TEXTVIEW("{0}").GetData(), {Exp->Value})));
	}
}
