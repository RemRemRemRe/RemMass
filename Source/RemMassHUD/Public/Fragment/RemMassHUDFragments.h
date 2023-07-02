// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassHUDFragments.generated.h"

class UWidget;

USTRUCT()
struct FRemMassHUDBindingFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "test")
	TSoftObjectPtr<UWidget> Widget;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UScriptStruct> FragmentType;
	
	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/RemMassHUD.RemMassHUDTask", ExcludeBaseStruct))
	FInstancedStruct Task;

	void UpdateWidget(FConstStructView StructView) const;
};
