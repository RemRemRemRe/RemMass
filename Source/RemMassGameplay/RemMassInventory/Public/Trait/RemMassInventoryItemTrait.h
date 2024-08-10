// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassInventoryItemTrait.generated.h"

UCLASS()
class REMMASSINVENTORY_API URemMassInventoryItemTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	virtual bool ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
