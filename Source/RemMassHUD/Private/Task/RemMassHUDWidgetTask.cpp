// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassHUDWidgetTask.h"

#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDWidgetTask)

void FRemMassHUDWidgetTask::DoWork(UWidget& OwningWidget, const TConstArrayView<FConstStructView> DataBindings) const
{
	RemCheckCondition(OwningWidget.IsA<UTextBlock>(), return;, REM_NO_LOG_BUT_ENSURE);

	auto& Text = static_cast<UTextBlock&>(OwningWidget);

	RemCheckCondition(DataBindings.Num() > 0, return;, REM_NO_LOG_BUT_ENSURE);
	
	if (auto* Level = DataBindings[0].GetPtr<const FRemMassLevelFragment>())
	{
		Text.SetText(FText::AsNumber(Level->Value));
	}
	else if (auto* Health = DataBindings[0].GetPtr<const FRemMassHealthFragment>())
	{
		Text.SetText(FText::AsNumber(Health->Value));
	}
	else if (auto* Exp = DataBindings[0].GetPtr<const FRemMassExperienceFragment>())
	{
		Text.SetText(FText::AsNumber(Exp->Value));
	}
	else if (auto* LevelUpExp = DataBindings[0].GetPtr<const FRemMassLevelUpExperienceFragment>())
	{
		Text.SetText(FText::AsNumber(LevelUpExp->Value));
	}
}
