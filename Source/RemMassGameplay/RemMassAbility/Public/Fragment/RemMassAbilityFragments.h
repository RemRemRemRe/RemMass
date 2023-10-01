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
struct FRemMassProjectileConfigAssetFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UMassEntityConfigAsset> ProjectileConfigAsset;
};

inline bool FRemMassHealthFragment::IsDead() const
{
	return !FAnimWeight::IsRelevant(Value);
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

USTRUCT()
struct FRemMassAbilityTreeRootsFragment : public FRemMassFragment
{
	GENERATED_BODY()
	
	/**
	 * root entity handle per tree
	 */
	Rem::Mass::Ability::FTreeNodeEntityArray Values;
};

USTRUCT()
struct FRemMassAbilityTreeChildrenNodesFragment : public FRemMassFragment
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
struct FRemMassProjectileTriggerInfoFragment : public FRemMassFragment
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
struct FRemMassProjectileTriggerStateFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float NextTriggeringTime{0.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 CurrentRounds{0};
	
	UPROPERTY(EditAnywhere)
	float NextShotTime{0.0f};
	
	UPROPERTY(EditAnywhere)
	uint8 CurrentShots{0};
};

USTRUCT()
struct FRemMassProjectileInfoFragment : public FRemMassFragment
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
