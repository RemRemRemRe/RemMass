// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassAbilityFragments.generated.h"

class UMassEntityConfigAsset;
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

USTRUCT()
struct FRemMassExpItemTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassExpCollectRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{100.0f};
};

USTRUCT()
struct FRemMassProjectileSpawnerFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SpawnInterval{1.0f};
	
	UPROPERTY(EditAnywhere)
	float InitialSpeed{500.0f};
	
	UPROPERTY(EditInstanceOnly)
	TWeakObjectPtr<UMassEntityConfigAsset> ProjectileConfigAsset;
};

USTRUCT()
struct FRemMassProjectileNextSpawnTimeFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{0.0f};
};

inline bool FRemMassHealthFragment::IsDead() const
{
	return FMath::IsNearlyZero(Value);
}

USTRUCT()
struct FRemMassMonsterTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassProjectileTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassOwnedProjectileSpawnersFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly)
	TArray<TWeakObjectPtr<UMassEntityConfigAsset>> ProjectileSpawnerConfigs;
};
