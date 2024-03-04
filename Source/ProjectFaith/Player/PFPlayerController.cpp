// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectFaith/Input/PFInputComponent.h"
#include "EnhancedInputComponent.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"


APFPlayerController::APFPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
	
}

void APFPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void APFPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();

	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		//ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void APFPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void APFPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GetASC()->AbilityInputTagReleased(InputTag);
}

void APFPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}


void APFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PFContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PFContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void APFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UPFInputComponent* PFInputComponent = CastChecked<UPFInputComponent>(InputComponent);
	PFInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APFPlayerController::Move);
	PFInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

UPFAbilitySystemComponent* APFPlayerController::GetASC()
{
	if (PFAbilitySystemComponent == nullptr)
	{
		PFAbilitySystemComponent = Cast<UPFAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return PFAbilitySystemComponent;
}

