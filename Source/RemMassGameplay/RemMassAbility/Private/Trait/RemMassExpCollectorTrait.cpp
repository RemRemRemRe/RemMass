// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassExpCollectorTrait.h"

#include "MassEntityTemplateRegistry.h"

void URemMassExpCollectorTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(Radius));
}
