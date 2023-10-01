// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassProjectileSpawnerTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "MassEntityConfigAsset.h"

void URemMassProjectileSpawnerTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::BuildTemplate(BuildContext, World);
	
	auto& ProjectileConfigAssetFragment = BuildContext.AddFragment_GetRef<FRemMassProjectileConfigAssetFragment>();
	ProjectileConfigAssetFragment.ProjectileConfigAsset = ProjectileConfigAsset;

	BuildContext.AddFragment<FRemMassProjectileTriggerStateFragment>();
}
