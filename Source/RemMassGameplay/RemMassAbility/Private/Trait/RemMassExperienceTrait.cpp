// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassExperienceTrait.h"

#include "MassEntityTemplateRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassExperienceTrait)

void URemMassExperienceTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(ExperienceType));
}
