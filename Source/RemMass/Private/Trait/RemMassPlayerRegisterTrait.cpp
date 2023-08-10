// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassPlayerRegisterTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "RemMassLog.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"
#include "Subsystem/RemMassGameStateSubsystem.h"

void URemMassPlayerRegisterTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	RemCheckCondition(BuildContext.HasTag<FRemMassPlayerTag>(), return;);

	BuildContext.GetMutableObjectFragmentInitializers().Add([&World](UObject& Owner, const FMassEntityView& EntityView,
		const EMassTranslationDirection)
	{
		World.GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(&Owner, [&World, &Owner, EntityView]
		{
			auto& GameStateSubsystem = *World.GetSubsystem<URemMassGameStateSubsystem>();
			GameStateSubsystem.AddPlayerEntity(Cast<APawn>(&Owner));

			const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
			EntityManager.Defer().AddTag<FRemMassPlayerRegisteredTag>(EntityView.GetEntity());
		}));
	});
}

void URemMassPlayerRegisterTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::ValidateTemplate(BuildContext, World);
	
	if (!BuildContext.HasTag<FRemMassPlayerTag>())
	{
		REM_LOG_FUNCTION(LogRemMass, Error, TEXT("{0} is required for a player entity"), FRemMassPlayerTag::StaticStruct()->GetName());
	}
}
