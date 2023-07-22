// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemWidgetComponentBase.h"
#include "Fragment/RemMassHUDFragments.h"
#include "RemMassHUDBinder.generated.h"

USTRUCT()
struct FRemMassHUDBinding
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWidget> Widget;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<const UScriptStruct>> FragmentTypes;

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/RemMassHUD.RemMassHUDTask", ExcludeBaseStruct))
	FInstancedStruct Task;

#if WITH_EDITORONLY_DATA

private:
	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/MassEntity.MassFragment", ExcludeBaseStruct))
	TArray<FInstancedStruct> SelectedFragments;

	friend class URemMassHUDBinder;
	
#endif

public:
	static auto TransformBinding(const FRemMassHUDBinding& Binding) -> FRemMassHUDBindingFragment;
	static auto TransformBindings(TConstArrayView<FRemMassHUDBinding> Bindings) -> TArray<FRemMassHUDBindingFragment>;
};

/**
 * 
 */
UCLASS()
class REMMASSHUD_API URemMassHUDBinder : public URemWidgetComponentBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Binding", meta = (Categories = "HUD"))
	FGameplayTag WidgetTag;
	
	UPROPERTY(EditAnywhere, Category = "Binding", meta = (TitleProperty = Widget, ShowOnlyInnerProperties))
	TArray<FRemMassHUDBinding> Bindings;

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
#endif
	
};
