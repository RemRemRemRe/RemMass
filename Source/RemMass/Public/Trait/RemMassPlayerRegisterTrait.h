// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassEntityTraitBase.h"
#include "RemMassPlayerRegisterTrait.generated.h"

UCLASS()
class REMMASS_API URemMassPlayerRegisterTrait : public URemMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	virtual bool ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
