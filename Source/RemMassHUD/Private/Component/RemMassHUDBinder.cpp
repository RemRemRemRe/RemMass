// Copyright RemRemRemRe, All Rights Reserved.


#include "Component/RemMassHUDBinder.h"

#include "GameplayTagContainer.h"
#include "RemMassHUDTags.h"
#include "RemMassSpawner.h"
#include "Macro/RemAssertionMacros.h"
#include "SpawnDataGenerator/RemMassHUDEntityGenerator.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

void URemMassHUDBinder::BeginPlay()
{
	Super::BeginPlay();

	const auto* World = GetWorld();
	RemCheckVariable(World, return;);

	auto* GameStateSubsystem = World->GetSubsystem<URemMassGameStateSubsystem>();
	RemCheckVariable(GameStateSubsystem, return;);

	auto* HUDSpawner = GameStateSubsystem->GetMassSpawner(FGameplayTagQuery::MakeQuery_MatchTag(
		Rem::Common::GetDefaultRef<URemMassHUDTags>().GetHUDMassSpawnerTag()));
	RemCheckVariable(HUDSpawner, return;);

	for (auto& Generator : HUDSpawner->GetSpawnDataGenerators())
	{
		auto* HUDEntityGenerator = Cast<URemMassHUDEntityGenerator>(Generator.GeneratorInstance);
		
		if (!HUDEntityGenerator)
		{
			continue;	
		}

		//HUDEntityGenerator->AddSpawnData(WidgetTag, Bindings);
	}
}
