// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassFrameworkSettings.h"

#include "AbilitySystemComponent.h"
#include "RemInputHandlingEnhancedComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassFrameworkSettings)

URemMassFrameworkSettings::URemMassFrameworkSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemClass = UAbilitySystemComponent::StaticClass();
	InputHandlingClass = URemInputHandlingEnhancedComponent::StaticClass();
}
