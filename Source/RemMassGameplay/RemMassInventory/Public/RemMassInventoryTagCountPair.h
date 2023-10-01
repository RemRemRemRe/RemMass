// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassInventoryItemState.h"
#include "RemMassTagCountPair.h"
#include "RemMassInventoryTagCountPair.generated.h"

enum class ERemMassInventoryItemState : uint8;
class UMassEntityConfigAsset;

USTRUCT(BlueprintType)
struct FRemMassInventoryTagCountPair : public FRemMassTagCountPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ERemMassInventoryItemState State{ERemMassInventoryItemState::Picked};
};

USTRUCT()
struct FRemMassInventoryTagCountPairContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMassEntityConfigAsset> ConfigAsset;

	UPROPERTY(EditAnywhere)
	TArray<FRemMassInventoryTagCountPair> Pairs;
};
