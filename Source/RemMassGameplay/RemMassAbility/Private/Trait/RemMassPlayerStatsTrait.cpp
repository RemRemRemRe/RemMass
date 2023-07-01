// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassPlayerStatsTrait.h"

#include "MassEntityTemplateRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassPlayerStatsTrait)

void URemMassPlayerStatsTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment(FConstStructView::Make(CurveTable));
}
