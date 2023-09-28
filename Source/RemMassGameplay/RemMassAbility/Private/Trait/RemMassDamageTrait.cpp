// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassDamageTrait.h"

#include "MassEntityTemplateRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassDamageTrait)

void URemMassDamageTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	if (bDamageSource)
	{
		BuildContext.AddTag<FRemMassDamageSourceTag>();
		BuildContext.AddFragment(FConstStructView::Make(Damage));
		BuildContext.AddFragment(FConstStructView::Make(DamageRadius));
	}
	else
	{
		BuildContext.AddTag<FRemMassDamageTargetTag>();
	}
}
