// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RemMassStatics.generated.h"

struct FInstancedStruct;
class UMassAgentComponent;

UCLASS()
class REMMASS_API URemMassStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// UFUNCTION(BlueprintCallable, Category = "Rem|Mass|Fragment", meta = (WorldContext = WorldContextObject))
	static FInstancedStruct GetMassFragmentFromHandle(const UObject* WorldContextObject,
		const FMassEntityHandle EntityHandle,
		const FInstancedStruct& Struct);

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|Fragment", meta = (WorldContext = WorldContextObject))
	static FInstancedStruct GetMassFragmentFromAgent(const UObject* WorldContextObject,
		const UMassAgentComponent* Agent,
		const FInstancedStruct& Struct);
};
