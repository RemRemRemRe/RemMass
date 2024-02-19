// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassInventoryItemTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassInventoryLog.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemLogMacros.h"

void URemMassInventoryItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddTag<FRemMassInventoryItemTag>();
	BuildContext.AddFragment<FRemMassInventoryItemTagFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemCountFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemStateFragment>();
}

void URemMassInventoryItemTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::ValidateTemplate(BuildContext, World);

	if (!BuildContext.HasFragment<FRemMassOwnerFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassInventory, Error, TEXT("FRemMassOwnerFragment is missing"));
	}
}
