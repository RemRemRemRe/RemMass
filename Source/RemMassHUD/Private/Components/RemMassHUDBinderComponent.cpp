// Copyright RemRemRemRe. 2026. All Rights Reserved.

#include "Components/RemMassHUDBinderComponent.h"

#include "Components/RemComponentContainer.inl"
#include "GameplayTagContainer.h"
#include "RemComponentBasedWidget.h"
#include "RemMassHUDTags.h"
#include "RemMassStatics.inl"
#include "Components/Widget.h"
#include "Macro/RemAssertionMacros.h"
#include "SpawnDataGenerator/RemMassHUDEntityGenerator.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDBinderComponent)

FRemMassHUDBindingFragment FRemMassHUDBinding::TransformBinding(const FRemMassHUDBinding& Binding)
{
    if (auto TransformedBinding = TransformBindings({Binding});
        !TransformedBinding.IsEmpty())
    {
        return TransformedBinding.Top();
    }

    return {};
}

TArray<FRemMassHUDBindingFragment> FRemMassHUDBinding::TransformBindings(
    const TConstArrayView<FRemMassHUDBinding> Bindings)
{
    TArray<FRemMassHUDBindingFragment> TransformedBindings;
    TransformedBindings.Reserve(Bindings.Num());

    for (auto& Binding : Bindings)
    {
        FRemMassHUDBindingFragment BindingFragment{
            .Widget        = Binding.Widget.Get(),
            .FragmentTypes = FRemMassHUDBindingFragment::FFragmentArrayType{Binding.FragmentTypes},
            .Task          = Binding.Task
        };

        TransformedBindings.Add(BindingFragment);
    }

    return TransformedBindings;
}

void FRemMassHUDBinderComponent::Initialize(const FContext& Context)
{
    auto* Widget = FRemComponentBase::GetOwner<URemComponentBasedWidget>(Context);
    RemCheckVariable(Widget, return;);

    auto* HUDEntityGenerator = Rem::Mass::GetSpawnDataGenerator<URemMassHUDEntityGenerator>(Widget,
        FGameplayTagQuery::MakeQuery_MatchTag(Rem::GetDefaultRef<URemMassHUDTags>().GetHUDMassSpawnerTag()));
    RemCheckVariable(HUDEntityGenerator, return;);

    HUDEntityGenerator->AddSpawnData(WidgetTag, FRemMassHUDBinding::TransformBindings(Bindings));
}
