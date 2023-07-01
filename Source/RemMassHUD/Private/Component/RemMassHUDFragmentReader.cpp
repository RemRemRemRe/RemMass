// Copyright RemRemRemRe, All Rights Reserved.


#include "Component/RemMassHUDFragmentReader.h"

bool URemMassHUDFragmentReader::RequiresTick() const
{
	return true;
}

void URemMassHUDFragmentReader::Tick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
}

void URemMassHUDFragmentReader::BeginPlay()
{
	Super::BeginPlay();

	
}
