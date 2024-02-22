// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassHUDTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "Fragment/RemMassHUDFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDTrait)

void URemMassHUDTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FRemMassHUDBindingFragment>();
}
