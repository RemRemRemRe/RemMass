// Copyright RemRemRemRe, All Rights Reserved.


#include "Fragment/RemMassAbilityFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassAbilityFragments)

void FRemMassProjectileTriggerInfoFragment::Combine(const FRemMassProjectileTriggerInfoFragment& Other)
{
	TriggerInterval += Other.TriggerInterval;
	RoundsPerInterval += Other.RoundsPerInterval;
	RoundsInterval += Other.RoundsInterval;

	RoundsInterval = FMath::Min(TriggerInterval / RoundsPerInterval, RoundsInterval);
	
	ShotsPerRound += Other.ShotsPerRound;
	ShotsInterval += Other.ShotsInterval;
	
	ShotsInterval = FMath::Min(RoundsInterval / ShotsPerRound, ShotsInterval);
	
	EmissionStyle = Other.EmissionStyle;
}

void FRemMassProjectileInfoFragment::Combine(const FRemMassProjectileInfoFragment& Other)
{
	bCanExplode |= Other.bCanExplode;
	Efficient += Other.Efficient;
	InitialSpeed += Other.InitialSpeed;
}
