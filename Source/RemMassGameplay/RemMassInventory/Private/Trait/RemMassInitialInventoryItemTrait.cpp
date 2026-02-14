// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassInitialInventoryItemTrait.h"

#include "MassEntityConfigAsset.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "MassEntityTemplate.h"
#include "MassSpawnerSubsystem.h"
#include "Engine/World.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassInitialInventoryItemTrait)

void URemMassInitialInventoryItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddTag<FRemMassInventoryTag>();
	BuildContext.GetMutableObjectFragmentInitializers().Add([&World, this](UObject& Object, const FMassEntityView& EntityView, const EMassTranslationDirection)
	{
		const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
		EntityManager.Defer().PushCommand<FMassDeferredCreateCommand>([this, &World, &Object, OwnerHandle = EntityView.GetEntity()]
			(const FMassEntityManager& Manager)
		{
			auto& SpawnerSystem = *World.GetSubsystem<UMassSpawnerSubsystem>();

			TMap<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>> InitialItemEntities;

			for (const auto& Value : InitialItems)
			{
				RemCheckCondition(Value.ConfigAsset, continue;, REM_NO_LOG_BUT_ENSURE);

				auto& Template = Value.ConfigAsset->GetOrCreateEntityTemplate(World);
				RemCheckCondition(Template.GetTemplateData().HasFragment<FRemMassOwnerFragment>(), continue;, REM_NO_LOG_BUT_ENSURE);

				TPair<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>> InitialItemEntitiesPair{Value.ConfigAsset, TArray<FMassEntityHandle>{}};

				RemCheckCondition(Value.Pairs.Num() > 0, continue;, REM_NO_LOG_BUT_ENSURE);

				auto& Handles = InitialItemEntitiesPair.Value;
				Handles.Reserve(Value.Pairs.Num());

				SpawnerSystem.SpawnEntities(Template, Value.Pairs.Num(), Handles);

				// initialize item data
				for (int32 Index = 0; Index < Handles.Num(); ++Index)
				{
					const auto& Handle = Handles[Index];
					FMassEntityView View{Manager, Handle};

					const auto& Pair = Value.Pairs[Index];
					View.GetFragmentData<FRemMassOwnerFragment>().Value = OwnerHandle;
					View.GetFragmentData<FRemMassInventoryItemTagFragment>().Value = Pair.Tag;
					View.GetFragmentData<FRemMassInventoryItemCountFragment>().Value = Pair.Count;
				}

				// Rem::EventScheduler::SendEvent(&Object, TODO, FInstancedStruct::Make<FRemMassInventoryItemsInitialized>(&Manager, OwnerHandle, &InitialItemEntitiesPair));

				InitialItemEntities.FindOrAdd(InitialItemEntitiesPair.Key, std::move(InitialItemEntitiesPair.Value));
			}

			// Rem::EventScheduler::SendEvent(&Object, TODO, FInstancedStruct::Make<FRemMassInventoryInitialized>(&Manager, OwnerHandle, &InitialItemEntities));
		});
	});
}
