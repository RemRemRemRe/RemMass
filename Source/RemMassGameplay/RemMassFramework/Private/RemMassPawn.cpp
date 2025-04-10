// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassPawn.h"
#include "MassAgentComponent.h"
#include "RemMassFrameworkSettings.h"
#include "Macro/RemAssertionMacros.h"
#include "RemInputHandlingComponent.h"
#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassPawn)

ARemMassPawn::ARemMassPawn(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	const auto& GameFrameworkSettings = Rem::GetDefaultRef<URemMassFrameworkSettings>();

	MassAgent = ObjectInitializer.CreateDefaultSubobject<UMassAgentComponent>(this, FName{TEXTVIEW("MassAgent")});

	// construct AbilitySystem
	{
		const auto& AbilitySystemClass = GameFrameworkSettings.GetAbilitySystemClass();

		// Create ability system component, and set it to be explicitly replicated
		AbilitySystem = Cast<UAbilitySystemComponent>(ObjectInitializer.CreateDefaultSubobject(this, FName{TEXTVIEW("AbilitySystem")},
				AbilitySystemClass, AbilitySystemClass, true, false));

		RemCheckVariable(AbilitySystem, return);
	}

	// construct InputHandling
	{
		const auto& InputHandlingClass = GameFrameworkSettings.GetInputHandlingClass();
		InputHandling = Cast<URemInputHandlingComponent>(ObjectInitializer.CreateDefaultSubobject(this, FName{TEXTVIEW("InputHandling")},
			InputHandlingClass, InputHandlingClass, true, false));

		RemCheckVariable(InputHandling);
	}
}

void ARemMassPawn::PawnClientRestart()
{
	Restart();
}

UPawnMovementComponent* ARemMassPawn::GetMovementComponent() const
{
	// return Super::GetMovementComponent();
	return nullptr;
}
