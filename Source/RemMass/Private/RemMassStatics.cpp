// Copyright RemRemRemRe, All Rights Reserved.


#include "RemMassStatics.h"

#include "GameplayTagContainer.h"
#include "MassEntitySubsystem.h"
#include "Macro/RemAssertionMacros.h"
#include "MassAgentComponent.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassStatics)

FInstancedStruct URemMassStatics::GetMassFragmentFromHandle(const UObject* WorldContextObject, const FMassEntityHandle EntityHandle, const FInstancedStruct& Struct)
{
	RemCheckVariable(WorldContextObject, return {});
	RemCheckVariable(EntityHandle, return {});
	RemCheckVariable(Struct, return {});
	
	// Fetch NetID if it exist
	const UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(WorldContextObject->GetWorld());
	RemCheckVariable(EntitySubsystem, return {});

	const auto StructView = EntitySubsystem->GetEntityManager().GetFragmentDataStruct(EntityHandle, Struct.GetScriptStruct());
	RemCheckVariable(StructView, return {});
	
	return FInstancedStruct{StructView};	
}

FInstancedStruct URemMassStatics::GetMassFragmentFromAgent(const UObject* WorldContextObject,
	const UMassAgentComponent* Agent, const FInstancedStruct& Struct)
{
	RemCheckVariable(Agent, return {});
	return GetMassFragmentFromHandle(WorldContextObject, Agent->GetEntityHandle(), Struct);
}

ARemMassSpawner* URemMassStatics::GetMassSpawner(const UObject* WorldContextObject, const FGameplayTagQuery& Query)
{
	RemCheckVariable(WorldContextObject, return {};);
	
	const auto* World = WorldContextObject->GetWorld();
	RemCheckVariable(World, return {};);

	auto* GameStateSubsystem = World->GetSubsystem<URemMassGameStateSubsystem>();
	RemCheckVariable(GameStateSubsystem, return {};);

	return GameStateSubsystem->GetMassSpawner(Query);
}
