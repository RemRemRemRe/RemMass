// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassOwnedProjectileSpawnersTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "MassEntityConfigAsset.h"
#include "MassSpawnerSubsystem.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassOwnedProjectileSpawnersTrait)

void URemMassOwnedProjectileSpawnersTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddFragment_GetRef<FRemMassOwnedProjectileSpawnersFragment>().ProjectileSpawnerConfigs =
		TArray<TWeakObjectPtr<UMassEntityConfigAsset>>{ProjectileSpawnerConfigs};

	BuildContext.GetMutableObjectFragmentInitializers().Add([&World, this](UObject&, const FMassEntityView& EntityView,
		const EMassTranslationDirection)
	{
		const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
		EntityManager.Defer().PushCommand<FMassDeferredCreateCommand>([&World, OwnerHandle = EntityView.GetEntity(), this]
			(const FMassEntityManager& System)
		{
			auto& SpawnerSystem = *World.GetSubsystem<UMassSpawnerSubsystem>();
			for (const auto& Config : ProjectileSpawnerConfigs)
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
