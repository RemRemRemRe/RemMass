// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassOwnedProjectileSpawnersTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "MassEntityConfigAsset.h"
#include "MassSpawnerSubsystem.h"

void URemMassOwnedProjectileSpawnersTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	TArray<TWeakObjectPtr<UMassEntityConfigAsset>> WeakProjectileSpawnerConfigs{};

	Algo::Transform(ProjectileSpawnerConfigs, WeakProjectileSpawnerConfigs,
		[](const TObjectPtr<UMassEntityConfigAsset>& ConfigAsset)
	{
		return TWeakObjectPtr<UMassEntityConfigAsset>{ConfigAsset};
	});

	BuildContext.AddFragment_GetRef<FRemMassOwnedProjectileSpawnersFragment>().ProjectileSpawnerConfigs = std::move(WeakProjectileSpawnerConfigs);

	BuildContext.GetMutableObjectFragmentInitializers().Add([&World, This{this}](UObject& Owner, const FMassEntityView& EntityView,
		const EMassTranslationDirection)
	{
		const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
		EntityManager.Defer().PushCommand<FMassDeferredCreateCommand>([&SavedConfigs = This->ProjectileSpawnerConfigs, &World, OwnerHandle = EntityView.GetEntity()]
			(const FMassEntityManager& System)
		{
			auto& SpawnerSystem = *World.GetSubsystem<UMassSpawnerSubsystem>();
			for (auto& Config : SavedConfigs)
			{
				auto& Template = Config->GetOrCreateEntityTemplate(World);
				TArray<FMassEntityHandle> Handles;
				SpawnerSystem.SpawnEntities(Template, 1, Handles);

				RemCheckCondition(Handles.Num() > 0, continue;, REM_NO_LOG_BUT_ENSURE);
				
				FMassEntityView View{System, Handles[0]};
				View.GetFragmentData<FRemMassOwnerFragment>().Value = OwnerHandle;
			}
		});
	});
}
