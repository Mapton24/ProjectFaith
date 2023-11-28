// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCharacter.h"
#include "PFCharacterMain.generated.h"

class APFPlayerState;
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API APFCharacterMain : public APFCharacter
{
	GENERATED_BODY()

	APFCharacterMain();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;


protected:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* MainCamera;

	UPROPERTY()
	APFPlayerState* PFPlayerState; 
};
