// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"

#include "PFPlayerController.generated.h"

class UPFInputConfig;
struct FGameplayTag;
struct FGenericTeamId;

class APawn;
class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;
struct FFrame;
struct FInputActionValue;

/**
 * 
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class PROJECTFAITH_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APFPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PlayerTick(float DeltaTime) override;

private:
	void Move(const FInputActionValue& ActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PFContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UPFInputConfig> InputConfig;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	
};
