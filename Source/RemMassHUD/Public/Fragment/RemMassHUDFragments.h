// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassHUDFragments.generated.h"

class UTextBlock;

USTRUCT()
struct FRemMassHUDBindingFragment : FRemMassFragment
{
	GENERATED_BODY()
	
};

USTRUCT()
struct FRemMassHUDTextBlockBindingFragment : FRemMassHUDBindingFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTextBlock> TextBlock;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UScriptStruct> FragmentType;
};
