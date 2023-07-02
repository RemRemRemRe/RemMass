// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassHUDTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "Fragment/RemMassHUDFragments.h"

void URemMassHUDTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FRemMassHUDBindingFragment>();
}
