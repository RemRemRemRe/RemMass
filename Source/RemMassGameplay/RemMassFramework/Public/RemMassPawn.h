// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "RemMassPawn.generated.h"

class UAbilitySystemComponent;
class URemInputHandlingComponent;
class UMassAgentComponent;

UCLASS()
class REMMASSFRAMEWORK_API ARemMassPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Mass, BlueprintGetter = "GetMassAgent")
	UMassAgentComponent* MassAgent;

	UPROPERTY(EditAnywhere, Category = Ability, BlueprintGetter = "GetAbilitySystem")
	UAbilitySystemComponent* AbilitySystem;
	
	UPROPERTY(EditAnywhere, Category = Input, BlueprintGetter = "GetInputHandling")
	URemInputHandlingComponent* InputHandling;
	
public:
	ARemMassPawn(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Rem|Mass")
	UMassAgentComponent* GetMassAgent() const;

	UFUNCTION(BlueprintCallable, Category = "Rem|Ability")
	UAbilitySystemComponent* GetAbilitySystem() const;
	
	UFUNCTION(BlueprintCallable, Category = "Rem|Input")
	URemInputHandlingComponent* GetInputHandling() const;
	
protected:
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	virtual void PawnClientRestart() override;
};

inline UMassAgentComponent* ARemMassPawn::GetMassAgent() const
{
	return MassAgent;
}

inline UAbilitySystemComponent* ARemMassPawn::GetAbilitySystem() const
{
	return AbilitySystem;
}

inline URemInputHandlingComponent* ARemMassPawn::GetInputHandling() const
{
	return InputHandling;
}
