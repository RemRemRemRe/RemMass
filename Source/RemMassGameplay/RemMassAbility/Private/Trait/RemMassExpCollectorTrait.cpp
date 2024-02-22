// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassExpCollectorTrait.h"

#include "MassEntityTemplateRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassExpCollectorTrait)

void URemMassExpCollectorTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(Radius));
}
