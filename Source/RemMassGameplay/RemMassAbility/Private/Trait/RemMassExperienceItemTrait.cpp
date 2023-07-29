// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassExperienceItemTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemLogMacros.h"
#include "RemMisc.h"

void URemMassExperienceItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddTag<FRemMassExpItemTag>();
}

void URemMassExperienceItemTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::ValidateTemplate(BuildContext, World);

	if (!BuildContext.HasFragment<FRemMassExperienceTypeFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassAbility, Error, TEXT("{0} is required for experience item"), FRemMassExperienceTypeFragment::StaticStruct()->GetName());
	}
}
