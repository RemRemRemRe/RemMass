// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassProjectileBoosterTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"
#include "Macro/RemLogMacros.h"

void URemMassProjectileBoosterTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(ProjectileTrigger));
	BuildContext.AddFragment(FConstStructView::Make(ProjectileInfo));
}

void URemMassProjectileBoosterTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::ValidateTemplate(BuildContext, World);

	if (!BuildContext.HasFragment<FRemMassOwnerFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassAbility, Error, TEXT("FRemMassOwnerFragment is missing"));
	}
}
