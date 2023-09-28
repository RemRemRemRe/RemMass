// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassHealthTrait.h"

#include "MassEntityTemplateRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHealthTrait)

void URemMassHealthTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(Health));
}
