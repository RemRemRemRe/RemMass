// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassAbilityFragments.generated.h"

enum class ERemMassAbilitySizeType : uint8;

class UCurveTable;

USTRUCT()
struct FRemMassHealthFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{100.0f};

	bool IsDead() const;
};

USTRUCT()
struct FRemMassDamageSourceTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassDamageTargetTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassDamageRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{500.0f};
};

USTRUCT()
struct FRemMassDamageFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{5.0f};
};

USTRUCT()
struct FRemMassDeadTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassRespawnRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{2000.0f};
};

USTRUCT()
struct FRemMassExperienceTypeFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ERemMassAbilitySizeType Value{};
};

USTRUCT()
struct FRemMassExperienceFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value{0};
};

USTRUCT()
struct FRemMassLevelUpExperienceFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value{0};
};

USTRUCT()
struct FRemMassLevelCurveTableFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UCurveTable> Value;
};

USTRUCT()
struct FRemMassLevelFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	uint8 Value{1};
};

inline bool FRemMassHealthFragment::IsDead() const
{
	return FMath::IsNearlyZero(Value);
}
