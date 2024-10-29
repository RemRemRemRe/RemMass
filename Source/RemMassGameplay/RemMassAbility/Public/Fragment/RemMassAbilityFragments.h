// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Fragment/RemMassGameFrameworkFragment.h"
#include "RemMassAbilityFragments.generated.h"

class UMassEntityConfigAsset;
enum class ERemMassAbilitySizeType : uint8;

class UCurveTable;


namespace Rem::Mass::Ability
{
	using FTreeNodeNumType = uint8;
	constexpr FTreeNodeNumType TreeNodeMaxNum = 8;
	using FTreeNodeEntityArray = TStaticArray<FMassEntityHandle, TreeNodeMaxNum>;
}

USTRUCT()
struct REMMASSABILITY_API FRemMassHealthFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{100.0f};

	bool IsDead() const;
};

USTRUCT()
struct REMMASSABILITY_API FRemMassDamageSourceTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassDamageTargetTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassDamageRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{500.0f};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassDamageFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{5.0f};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassDeadTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassRespawnRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{2000.0f};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassExperienceTypeFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ERemMassAbilitySizeType Value{};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassExperienceFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value{0};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassLevelUpExperienceFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value{0};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassLevelCurveTableFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UCurveTable> Value;
};

USTRUCT()
struct REMMASSABILITY_API FRemMassLevelFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	uint8 Value{1};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassExpItemTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassExpCollectRadiusFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value{100.0f};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassProjectileConfigAssetFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UMassEntityConfigAsset> ProjectileConfigAsset;
};

USTRUCT()
struct REMMASSABILITY_API FRemMassMonsterTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassProjectileTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASSABILITY_API FRemMassOwnedProjectileSpawnersFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly)
	TArray<TWeakObjectPtr<UMassEntityConfigAsset>> ProjectileSpawnerConfigs;
};

USTRUCT()
struct REMMASSABILITY_API FRemMassAbilityTreeRootsFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	/**
	 * root entity handle per tree
	 */
	Rem::Mass::Ability::FTreeNodeEntityArray Values;
};

USTRUCT()
struct REMMASSABILITY_API FRemMassAbilityTreeChildrenNodesFragment : public FRemMassFragment
{
	GENERATED_BODY()

private:
	Rem::Mass::Ability::FTreeNodeNumType Num{0};
	
	/**
	 * children entities per tree node
	 */
	Rem::Mass::Ability::FTreeNodeEntityArray Values;

public:
	Rem::Mass::Ability::FTreeNodeNumType GetNum() const;
	const Rem::Mass::Ability::FTreeNodeEntityArray& GetValues() const;

	FMassEntityHandle GetEntityHandle(Rem::Mass::Ability::FTreeNodeNumType Index) const;
	void Add(FMassEntityHandle EntityHandle);
	void Remove();
};

UENUM(BlueprintType)
enum class ERemMassProjectileEmissionStyle : uint8
{
	//											*							* * *
	LeftRightLayout // if shot count is 3: * actor *, if shot count is 5: * actor *
};

USTRUCT()
struct REMMASSABILITY_API FRemMassProjectileTriggerInfoFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float TriggerInterval{1.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 RoundsPerInterval{1};

	UPROPERTY(EditAnywhere)
	float RoundsInterval{1.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 ShotsPerRound{1};
	
	UPROPERTY(EditAnywhere)
	float ShotsInterval{1.0f};
	
	UPROPERTY(EditAnywhere)
	ERemMassProjectileEmissionStyle EmissionStyle{};

	void Combine(const FRemMassProjectileTriggerInfoFragment& Other);
};

USTRUCT()
struct REMMASSABILITY_API FRemMassProjectileTriggerStateFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double NextTriggeringTime{0.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 CurrentRounds{0};
	
	UPROPERTY(EditAnywhere)
	double NextShotTime{0.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 CurrentShots{0};
};

USTRUCT()
struct REMMASSABILITY_API FRemMassProjectileInfoFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	bool bCanExplode{false};
	
	UPROPERTY(EditAnywhere)
	float Efficient{1.0f};
	
	UPROPERTY(EditAnywhere)
	float InitialSpeed{500.0f};

	void Combine(const FRemMassProjectileInfoFragment& Other);
};

inline Rem::Mass::Ability::FTreeNodeNumType FRemMassAbilityTreeChildrenNodesFragment::GetNum() const
{
	return Num;
}

inline const Rem::Mass::Ability::FTreeNodeEntityArray& FRemMassAbilityTreeChildrenNodesFragment::GetValues() const
{
	return Values;
}

inline FMassEntityHandle FRemMassAbilityTreeChildrenNodesFragment::GetEntityHandle(const Rem::Mass::Ability::FTreeNodeNumType Index) const
{
	return Values[Index];
}

inline void FRemMassAbilityTreeChildrenNodesFragment::Add(const FMassEntityHandle EntityHandle)
{
	Values[Num] = EntityHandle;
	++Num;
}

inline void FRemMassAbilityTreeChildrenNodesFragment::Remove()
{
	const auto NewNum = --Num;
	Values[NewNum] = {};
	Num = NewNum;
}
