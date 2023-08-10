// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassProjectileSpawnerTrait.h"

#include "MassEntityTemplateRegistry.h"

void URemMassProjectileSpawnerTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	auto& SpawnerFragment = BuildContext.AddFragment_GetRef<FRemMassProjectileSpawnerFragment>();

	SpawnerFragment.SpawnInterval = SpawnInterval;
	SpawnerFragment.InitialSpeed = InitialSpeed;
	SpawnerFragment.ProjectileConfigAsset = ProjectileConfigAsset;
	
	BuildContext.AddFragment<FRemMassProjectileNextSpawnTimeFragment>();
	BuildContext.AddFragment<FRemMassOwnerFragment>();
}
