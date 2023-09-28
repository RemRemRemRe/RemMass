// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassInventoryItemTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "Fragment/RemMassInventoryFragments.h"

void URemMassInventoryItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddTag<FRemMassInventoryItemTag>();
	BuildContext.AddFragment<FRemMassOwnerFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemTagFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemCountFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemStateFragment>();
}
