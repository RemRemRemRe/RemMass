// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassExperienceItemTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemLogMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassExperienceItemTrait)

void URemMassExperienceItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddTag<FRemMassExpItemTag>();
}

bool URemMassExperienceItemTrait::ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World,
	FAdditionalTraitRequirements& OutTraitRequirements) const
{
	if (!BuildContext.HasFragment<FRemMassExperienceTypeFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassAbility, Error, TEXT("{0} is required for experience item"), FRemMassExperienceTypeFragment::StaticStruct()->GetName());
		return false;
	}
	
	return Super::ValidateTemplate(BuildContext, World, OutTraitRequirements);
}
