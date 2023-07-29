// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RemMassStatics.generated.h"

struct FMassEntityHandle;
struct FGameplayTagQuery;
class ARemMassSpawner;
struct FInstancedStruct;
class UMassAgentComponent;

UCLASS()
class REMMASS_API URemMassStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintCallable, Category = "Rem|Mass|Fragment", meta = (WorldContext = WorldContextObject))
	static FInstancedStruct GetMassFragmentFromHandle(const UObject* WorldContextObject,
		const FMassEntityHandle EntityHandle,
		const FInstancedStruct& Struct);

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|Fragment", meta = (WorldContext = WorldContextObject))
	static FInstancedStruct GetMassFragmentFromAgent(const UObject* WorldContextObject,
		const UMassAgentComponent* Agent,
		const FInstancedStruct& Struct);

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass|Spawner", meta = (WorldContext = WorldContextObject))
	static ARemMassSpawner* GetMassSpawner(const UObject* WorldContextObject, const FGameplayTagQuery& Query);
};
