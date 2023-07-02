// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassSpawner.h"

#include "Macro/RemAssertionMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"


// Sets default values
ARemMassSpawner::ARemMassSpawner() = default;

void ARemMassSpawner::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	auto* GameStateSubsystem = GetWorld()->GetSubsystem<URemMassGameStateSubsystem>();
	RemCheckVariable(GameStateSubsystem, return;);

	GameStateSubsystem->RegisterMassSpawner(*this);
}
