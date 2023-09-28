// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "RemMassInventoryItemState.h"
#include "Fragment/RemMassGameFrameworkFragment.h"

#include "RemMassInventoryFragments.generated.h"

enum class ERemMassInventoryItemState : uint8;

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemTagFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag Value;
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemCountFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value{};
};

USTRUCT()
struct REMMASSINVENTORY_API FRemMassInventoryItemStateFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ERemMassInventoryItemState Value{ERemMassInventoryItemState::Picked};
};
