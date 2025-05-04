// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassPlayerRegisterTrait.h"

#include "MassCommandBuffer.h"
#include "MassEntityManager.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityUtils.h"
#include "MassEntityView.h"
#include "RemMassLog.h"
#include "TimerManager.h"
#include "Fragment/RemMassGameFrameworkFragment.h"
#include "GameFramework/Pawn.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"
#include "Object/RemObjectStatics.h"
#include "Subsystems/RemMassGameStateSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassPlayerRegisterTrait)

void URemMassPlayerRegisterTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	RemCheckCondition(BuildContext.HasTag<FRemMassPlayerTag>(), return;);

	BuildContext.GetMutableObjectFragmentInitializers().Add([&World](UObject& Owner, const FMassEntityView& EntityView,
		const EMassTranslationDirection)
	{
		Rem::Object::SetTimerForThisTick(World, Rem::FTimerDelegate::CreateWeakLambda(&Owner, [&World, &Owner, EntityView]
		{
			auto& GameStateSubsystem = *World.GetSubsystem<URemMassGameStateSubsystem>();
			GameStateSubsystem.AddPlayerEntity(Cast<APawn>(&Owner));

			const auto& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
			EntityManager.Defer().AddTag<FRemMassPlayerRegisteredTag>(EntityView.GetEntity());
		}));
	});
}

bool URemMassPlayerRegisterTrait::ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const
{
	if (!BuildContext.HasTag<FRemMassPlayerTag>())
	{
		REM_LOG_FUNCTION(LogRemMass, Error, TEXT("{0} is required for a player entity"), FRemMassPlayerTag::StaticStruct()->GetName());
		return false;
	}

	return Super::ValidateTemplate(BuildContext, World, OutTraitRequirements);
}
