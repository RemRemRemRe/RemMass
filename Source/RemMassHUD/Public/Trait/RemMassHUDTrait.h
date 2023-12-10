// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Trait/RemMassEntityTraitBase.h"
#include "RemMassHUDTrait.generated.h"


UCLASS()
class REMMASSHUD_API URemMassHUDTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
