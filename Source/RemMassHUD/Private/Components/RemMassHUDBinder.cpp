// Copyright RemRemRemRe, All Rights Reserved.


#include "Components/RemMassHUDBinder.h"

#include "GameplayTagContainer.h"
#include "RemMassHUDTags.h"
#include "RemMassStatics.inl"
#include "Components/Widget.h"
#include "Macro/RemAssertionMacros.h"
#include "SpawnDataGenerator/RemMassHUDEntityGenerator.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassHUDBinder)

auto FRemMassHUDBinding::TransformBinding(const FRemMassHUDBinding& Binding) -> FRemMassHUDBindingFragment
{
	if (auto TransformedBinding = TransformBindings({Binding});
		!TransformedBinding.IsEmpty())
	{
		return TransformedBinding.Top();
	}

	return {};
}

auto FRemMassHUDBinding::TransformBindings(const TConstArrayView<FRemMassHUDBinding> Bindings) -> TArray<FRemMassHUDBindingFragment>
{
	TArray<FRemMassHUDBindingFragment> TransformedBindings;
	TransformedBindings.Reserve(Bindings.Num());

	for (auto& Binding : Bindings)
	{
		FRemMassHUDBindingFragment BindingFragment{
			.Widget = Binding.Widget.Get(),
			.FragmentTypes = FRemMassHUDBindingFragment::FFragmentArrayType{Binding.FragmentTypes},
			.Task = Binding.Task};

		TransformedBindings.Add(BindingFragment);
	}

	return TransformedBindings;
}

void URemMassHUDBinder::BeginPlay()
{
	Super::BeginPlay();

	auto* HUDEntityGenerator = Rem::Mass::GetSpawnDataGenerator<URemMassHUDEntityGenerator>(this,
		FGameplayTagQuery::MakeQuery_MatchTag(Rem::GetDefaultRef<URemMassHUDTags>().GetHUDMassSpawnerTag()));
	RemCheckVariable(HUDEntityGenerator, return;);

	HUDEntityGenerator->AddSpawnData(WidgetTag, FRemMassHUDBinding::TransformBindings(Bindings));
}

#if WITH_EDITOR

void URemMassHUDBinder::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}

#endif
