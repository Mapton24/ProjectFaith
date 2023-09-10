// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/MovementInterface.h"
#include "ProjectFaithCharacterBase.generated.h"

UCLASS(Config = Game, Meta = (ShortTooltip = "Base character of Project Faith."))
class PROJECTFAITH_API AProjectFaithCharacterBase : public ACharacter, public IMovementInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectFaithCharacterBase();

	void CheckIfCharacterHasMesh();

protected:

	void Move_Implementation(const FInputActionValue& Value);

	void Jump_Implementation();

	void StopJumping_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
