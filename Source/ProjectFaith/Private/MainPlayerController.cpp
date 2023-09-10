// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/MovementInterface.h"


void AMainPlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainPlayerController::StopJumping);

		//Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	}

}

void AMainPlayerController::Jump()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UMovementInterface::StaticClass())) {
		IMovementInterface::Execute_Jump(pawn);
	}
}
void AMainPlayerController::StopJumping()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UMovementInterface::StaticClass())) {
		IMovementInterface::Execute_StopJumping(pawn);
	}
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UMovementInterface::StaticClass())) {
		IMovementInterface::Execute_Move(pawn, Value);
	}
}
