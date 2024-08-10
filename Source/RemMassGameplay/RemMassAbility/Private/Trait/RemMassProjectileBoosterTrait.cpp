// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassProjectileBoosterTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"
#include "Macro/RemLogMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassProjectileBoosterTrait)

void URemMassProjectileBoosterTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(ProjectileTrigger));
	BuildContext.AddFragment(FConstStructView::Make(ProjectileInfo));
}

bool URemMassProjectileBoosterTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	if (!BuildContext.HasFragment<FRemMassOwnerFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassAbility, Error, TEXT("FRemMassOwnerFragment is missing"));
		return false;
	}
	return Super::ValidateTemplate(BuildContext, World);
}
