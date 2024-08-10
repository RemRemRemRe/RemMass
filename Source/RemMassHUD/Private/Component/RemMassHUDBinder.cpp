// Copyright RemRemRemRe, All Rights Reserved.


#include "Component/RemMassHUDBinder.h"

#include "GameplayTagContainer.h"
#include "RemMassHUDTags.h"
#include "RemMassStatics.inl"
#include "Components/Widget.h"
#include "Macro/RemAssertionMacros.h"
#include "Object/RemObjectStatics.h"
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

	RemCheckVariable(PropertyChangedEvent.Property, return;, REM_NO_LOG_BUT_ENSURE);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(FRemMassHUDBinding, SelectedFragments)
		&& Rem::Object::IsOnlyArrayElementChanged(PropertyChangedEvent.ChangeType))
	{
		const auto Index = PropertyChangedEvent.GetArrayIndex(GET_MEMBER_NAME_STRING_CHECKED(ThisClass, Bindings));

		RemCheckCondition(Bindings.IsValidIndex(Index), return;, REM_NO_LOG_BUT_ENSURE);

		auto& Binding = Bindings[Index];

		TArray<TObjectPtr<const UScriptStruct>> FragmentTypes{};
		const auto& InstancedStructs = Binding.SelectedFragments;
		FragmentTypes.Reserve(InstancedStructs.Num());

		for (auto& Struct : InstancedStructs)
		{
			FragmentTypes.Add(Struct.GetScriptStruct());
		}

		Binding.FragmentTypes = std::move(FragmentTypes);
	}
}

#endif
