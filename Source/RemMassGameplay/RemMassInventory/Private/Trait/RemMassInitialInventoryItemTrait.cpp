// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassInitialInventoryItemTrait.h"

#include "MassEntityConfigAsset.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "MassEntityTemplate.h"
#include "MassSpawnerSubsystem.h"
#include "RemEventSchedulerInterface.h"
#include "RemEventSchedulerStatics.h"
#include "Event/RemMassInventoryInitialized.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemAssertionMacros.h"

void URemMassInitialInventoryItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddTag<FRemMassInventoryTag>();
	BuildContext.GetMutableObjectFragmentInitializers().Add([&World, This(this)](UObject& Object, FMassEntityView& EntityView, const EMassTranslationDirection)
	{
		const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
		EntityManager.Defer().PushCommand<FMassDeferredCreateCommand>([This, &World, &Object, OwnerHandle = EntityView.GetEntity()]
			(FMassEntityManager& Manager)
		{
			auto& SpawnerSystem = *World.GetSubsystem<UMassSpawnerSubsystem>();
			
			TMap<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>> InitialItemEntities;

			const auto EventScheduler = URemEventSchedulerStatics::GetEventScheduler(&Object);
            RemCheckVariable(EventScheduler.GetObject(), return);
            			
			for (const auto& [ConfigAsset, Pairs] : This->InitialItems)
			{
				RemCheckCondition(ConfigAsset, continue;, REM_NO_LOG_BUT_ENSURE);
				
				auto& Template = ConfigAsset->GetOrCreateEntityTemplate(World);
				RemCheckCondition(Template.GetTemplateData().HasFragment<FRemMassOwnerFragment>(), continue;, REM_NO_LOG_BUT_ENSURE);

				TPair<TObjectPtr<UMassEntityConfigAsset>, TArray<FMassEntityHandle>> InitialItemEntitiesPair{ConfigAsset, TArray<FMassEntityHandle>{}};
				
				RemCheckCondition(Pairs.Num() > 0, continue;, REM_NO_LOG_BUT_ENSURE);
				
				auto& Handles = InitialItemEntitiesPair.Value;
				Handles.Reserve(Pairs.Num());

				SpawnerSystem.SpawnEntities(Template, Pairs.Num(), Handles);

				// initialize item data
				for (int32 Index = 0; Index < Handles.Num(); ++Index)
				{
					const auto& Handle = Handles[Index];
					FMassEntityView View{Manager, Handle};

					const auto& [Tag, Count] = Pairs[Index];
					View.GetFragmentData<FRemMassOwnerFragment>().Value = OwnerHandle;
					View.GetFragmentData<FRemMassInventoryItemTagFragment>().Value = Tag;
					View.GetFragmentData<FRemMassInventoryItemCountFragment>().Value = Count;
				}

				EventScheduler->SendEvent(&Object, FInstancedStruct::Make<FRemMassInventoryItemsInitialized>(&Manager, OwnerHandle, &InitialItemEntitiesPair));
				
				InitialItemEntities.FindOrAdd(InitialItemEntitiesPair.Key, std::move(InitialItemEntitiesPair.Value));
			}

			EventScheduler->SendEvent(&Object, FInstancedStruct::Make<FRemMassInventoryInitialized>(&Manager, OwnerHandle, &InitialItemEntities));
		});
	});
}
