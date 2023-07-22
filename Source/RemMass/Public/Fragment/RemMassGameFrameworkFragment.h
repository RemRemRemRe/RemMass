// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "MassEntityTypes.h"

#include "RemMassGameFrameworkFragment.generated.h"

USTRUCT()
struct FRemMassFragment : public FMassFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassChunkFragment : public FMassChunkFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassSharedFragment : public FMassSharedFragment
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassLocalPlayerTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassPlayerTag : public FRemMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct FRemMassPlayerFragment : public FRemMassFragment
{
	GENERATED_BODY()
};
