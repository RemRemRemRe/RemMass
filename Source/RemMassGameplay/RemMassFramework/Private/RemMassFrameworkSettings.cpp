// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassFrameworkSettings.h"

#include "AbilitySystemComponent.h"
#include "RemInputHandlingComponent.h"

URemMassFrameworkSettings::URemMassFrameworkSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemClass = UAbilitySystemComponent::StaticClass();
	InputHandlingClass = URemInputHandlingComponent::StaticClass();
}
