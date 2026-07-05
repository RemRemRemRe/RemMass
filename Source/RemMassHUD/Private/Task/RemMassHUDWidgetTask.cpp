// Copyright RemRemRemRe, All Rights Reserved.


#include "Task/RemMassHUDWidgetTask.h"

#include "Components/TextBlock.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDWidgetTask)

void FRemMassHUDWidgetTask::DoWork(UWidget& OwningWidget,
    const TConstArrayView<FConstStructView> DataBindings) const
{
    RemCheckCondition(ensure, OwningWidget.IsA<UTextBlock>(), return;);

    auto& Text = static_cast<UTextBlock&>(OwningWidget);

    RemCheckCondition(ensure, DataBindings.Num() > 0, return;);

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
