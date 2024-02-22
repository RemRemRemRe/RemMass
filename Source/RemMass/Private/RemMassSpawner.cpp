// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassSpawner.h"

#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassSpawner)


// Sets default values
ARemMassSpawner::ARemMassSpawner() = default;

void ARemMassSpawner::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	auto* GameStateSubsystem = GetWorld()->GetSubsystem<URemMassGameStateSubsystem>();
	RemCheckVariable(GameStateSubsystem, return;);

	GameStateSubsystem->RegisterMassSpawner(*this);
}
