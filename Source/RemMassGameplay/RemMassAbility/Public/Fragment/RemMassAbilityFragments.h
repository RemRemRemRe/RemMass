// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityTypes.h"
#include "RemMassAbilityFragments.generated.h"

USTRUCT()
struct FRemMassHealthFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Transient)
	float Value{100.0f};

	bool IsDead() const;
};

USTRUCT()
struct FRemMassDamageSourceTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassDamageTargetTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassDamageRadiusFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Transient)
	float Value{500.0f};
};

USTRUCT()
struct FRemMassDamageFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Transient)
	float Value{5.0f};
};

USTRUCT()
struct FRemMassDeadTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassRespawnRadiusFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Transient)
	float Value{2000.0f};
};

inline bool FRemMassHealthFragment::IsDead() const
{
	return Value <= ZERO_ANIMWEIGHT_THRESH;
}
