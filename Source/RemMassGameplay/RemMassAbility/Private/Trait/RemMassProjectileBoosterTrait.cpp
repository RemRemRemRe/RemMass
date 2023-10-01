// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassProjectileBoosterTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"

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
		UE_LOG(LogRemMassAbility, Error, TEXT("FRemMassOwnerFragment is missing"));
	}
}
