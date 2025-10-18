// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemWidgetComponentBase.h"
#include "Fragment/RemMassHUDFragments.h"
#include "RemMassHUDBinder.generated.h"

struct FRemMassHUDTask;

USTRUCT()
struct FRemMassHUDBinding
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Rem")
	TSoftObjectPtr<UWidget> Widget;

	UPROPERTY(EditAnywhere, Category = "Rem", meta = (MetaStruct = "/Script/MassEntity.MassFragment"))
	TArray<TObjectPtr<const UScriptStruct>> FragmentTypes;

	UPROPERTY(EditAnywhere, Category = "Rem", meta = (ExcludeBaseStruct))
	TInstancedStruct<FRemMassHUDTask> Task;

	static auto TransformBinding(const FRemMassHUDBinding& Binding) -> FRemMassHUDBindingFragment;
	static auto TransformBindings(TConstArrayView<FRemMassHUDBinding> Bindings) -> TArray<FRemMassHUDBindingFragment>;
};


UCLASS()
class REMMASSHUD_API URemMassHUDBinder : public URemWidgetComponentBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Binding", meta = (GameplayTagFilter = "HUD"))
	FGameplayTag WidgetTag;
	
	UPROPERTY(EditAnywhere, Category = "Binding", meta = (TitleProperty = Widget, ShowOnlyInnerProperties))
	TArray<FRemMassHUDBinding> Bindings;

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
#endif
	
};
