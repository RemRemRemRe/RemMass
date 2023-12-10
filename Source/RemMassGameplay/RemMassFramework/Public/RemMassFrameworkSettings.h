// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Macro/RemGenerateMembersMacro.h"
#include "RemMassFrameworkSettings.generated.h"

class UAbilitySystemComponent;
class URemInputHandlingComponent;

UCLASS(defaultconfig, Config = RemMassFrameworkSettings, Const)
class REMMASSFRAMEWORK_API URemMassFrameworkSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category = "Character|Component")
	TSubclassOf<UAbilitySystemComponent> AbilitySystemClass;
	
	UPROPERTY(Config, EditAnywhere, Category = "Character|Component")
	TSubclassOf<URemInputHandlingComponent> InputHandlingClass;
	
public:
	URemMassFrameworkSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(AbilitySystemClass)
	REM_DEFINE_CONST_ONLY_GETTERS_RETURN_REFERENCE_SIMPLE(InputHandlingClass)
};
