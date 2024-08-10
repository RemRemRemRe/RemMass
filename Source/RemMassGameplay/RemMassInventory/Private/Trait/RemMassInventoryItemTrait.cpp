// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassInventoryItemTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassInventoryLog.h"
#include "Fragment/RemMassInventoryFragments.h"
#include "Macro/RemLogMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassInventoryItemTrait)

void URemMassInventoryItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddTag<FRemMassInventoryItemTag>();
	BuildContext.AddFragment<FRemMassInventoryItemTagFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemCountFragment>();
	BuildContext.AddFragment<FRemMassInventoryItemStateFragment>();
}

bool URemMassInventoryItemTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	if (!BuildContext.HasFragment<FRemMassOwnerFragment>())
	{
		REM_LOG_FUNCTION(LogRemMassInventory, Error, TEXT("FRemMassOwnerFragment is missing"));
		return false;
	}
	return Super::ValidateTemplate(BuildContext, World);
}
