// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityTypes.h"
#include "MassEntityHandle.h"

#include "RemMassGameFrameworkFragment.generated.h"

USTRUCT()
struct REMMASS_API FRemMassFragment : public FMassFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassChunkFragment : public FMassChunkFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassSharedFragment : public FMassSharedFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassLocalPlayerTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassPlayerTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct REMMASS_API FRemMassOwnerFragment : public FRemMassFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FMassEntityHandle Value;
};

USTRUCT()
struct REMMASS_API FRemMassPlayerRegisteredTag : public FRemMassTag
{
	GENERATED_BODY()
};
