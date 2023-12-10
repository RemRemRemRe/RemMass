// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassHUDFragments.generated.h"

struct FRemMassHUDTask;
class UWidget;

USTRUCT()
struct FRemMassHUDBindingFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY()
	TWeakObjectPtr<UWidget> Widget;

	using FFragmentArrayType = TArray<TWeakObjectPtr<const UScriptStruct>, TInlineAllocator<4>>;
	FFragmentArrayType FragmentTypes;
	
	UPROPERTY()
	TInstancedStruct<FRemMassHUDTask> Task;

	void UpdateWidget(TConstArrayView<FConstStructView> StructViews) const;

	bool IsValid() const;
};
