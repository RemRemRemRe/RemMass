// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "MassSpawner.h"
#include "Macro/RemGenerateMembersMacro.h"
#include "RemMassSpawner.generated.h"

UCLASS()
class REMMASS_API ARemMassSpawner : public AMassSpawner
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer ActorTags;

public:
	// Sets default values for this actor's properties
	ARemMassSpawner();

	virtual void PreInitializeComponents() override;

	REM_DEFINE_GETTERS_RETURN_REFERENCE(SpawnDataGenerators, TArray<FMassSpawnDataGenerator>, &SpawnDataGenerators)

	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE(ActorTags, FGameplayTagContainer, &ActorTags)
};
