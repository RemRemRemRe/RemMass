// Copyright RemRemRemRe. 2026. All Rights Reserved.

#pragma once

#include "Components/RemComponentContainer.h"
#include "Fragment/RemMassHUDFragments.h"
#include "GameplayTagContainer.h"

#include "RemMassHUDBinderComponent.generated.h"

class UWidget;
struct FRemMassHUDTask;

/**
 * Binding configuration authored on a widget: which widget tag to bind and how
 * the widget's bindings transfer to Mass HUD entities.
 *
 * The component pushes the binding data to the HUD entity generator in
 * Initialize (the widget self-drives component lifecycle after linking).
 */
USTRUCT()
struct REMMASSHUD_API FRemMassHUDBinding
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Rem")
    TSoftObjectPtr<UWidget> Widget;

    UPROPERTY(EditAnywhere, Category = "Rem", meta = (MetaStruct = "/Script/MassEntity.MassFragment"))
    TArray<TObjectPtr<const UScriptStruct>> FragmentTypes;

    UPROPERTY(EditAnywhere, Category = "Rem", meta = (ExcludeBaseStruct))
    TInstancedStruct<FRemMassHUDTask> Task;

    static FRemMassHUDBindingFragment TransformBinding(const FRemMassHUDBinding& Binding);
    static TArray<FRemMassHUDBindingFragment> TransformBindings(TConstArrayView<FRemMassHUDBinding> Bindings);
};

/**
 * Widget component: transfers the widget's HUD binding configuration to the
 * Mass HUD entity generator on Initialize (resurrects the previously dead
 * BeginPlay flow of URemMassHUDBinder).
 */
USTRUCT(DisplayName = "Mass HUD Binder")
struct REMMASSHUD_API FRemMassHUDBinderComponent : public FRemComponentBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Binding", meta = (GameplayTagFilter = "HUD"))
    FGameplayTag WidgetTag;

    UPROPERTY(EditAnywhere, Category = "Binding", meta = (TitleProperty = Widget, ShowOnlyInnerProperties))
    TArray<FRemMassHUDBinding> Bindings;

    virtual void Initialize(const FContext& Context) override;
};
