// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassEntitySpawnDataGeneratorBase.h"
#include "RemMassLog.h"
#include "Macro/RemCoreMiscDefines.h"
#include "RemMassEntitySpawnDataRegenerator.generated.h"

namespace Rem::Mass
{
	struct FScopedEntitySpawnDataRegeneration;
}

UCLASS(Abstract)
class REMMASS_API URemMassEntitySpawnDataRegenerator : public URemMassEntitySpawnDataGeneratorBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	TWeakObjectPtr<UObject> SavedQueryOwner;

	TConstArrayView<FMassSpawnedEntityType> SavedEntityTypes;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	int32 SavedCount;
	
	FFinishedGeneratingSpawnDataSignature SavedFinishedGeneratingSpawnPointsDelegate;
	
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
	bool bCachedData;

	friend struct Rem::Mass::FScopedEntitySpawnDataRegeneration;
	
	virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes, int32 Count,
		FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;
	
	virtual bool CanGenerate() const;
	virtual void GenerateInternal() const REM_VIRTUAL_WARN(LogRemMass);
	virtual void CleanUp() REM_VIRTUAL_WARN(LogRemMass);
};

namespace Rem::Mass
{

struct FScopedEntitySpawnDataRegeneration
{
private:
	URemMassEntitySpawnDataRegenerator& Regenerator;
	
public:
	explicit FScopedEntitySpawnDataRegeneration(URemMassEntitySpawnDataRegenerator& InRegenerator)
		: Regenerator(InRegenerator) {}
	
	~FScopedEntitySpawnDataRegeneration();
};

}

inline Rem::Mass::FScopedEntitySpawnDataRegeneration::~FScopedEntitySpawnDataRegeneration()
{
	if (Regenerator.CanGenerate())
	{
		Regenerator.GenerateInternal();
		Regenerator.CleanUp();
	}
}
