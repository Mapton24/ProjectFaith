// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectFaithCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AProjectFaithCharacterBase::AProjectFaithCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1, 0, 0));
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CheckIfCharacterHasMesh();
}

void AProjectFaithCharacterBase::CheckIfCharacterHasMesh()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();

	if (MeshComponent)
	{
		FVector NewLocation = MeshComponent->GetComponentLocation();
		NewLocation.Z = -88.00f;
		MeshComponent->SetWorldLocation(NewLocation);
	}
}

void AProjectFaithCharacterBase::Move_Implementation(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AProjectFaithCharacterBase::Jump_Implementation()
{
	Super::Jump();
}

void AProjectFaithCharacterBase::StopJumping_Implementation()
{
	Super::StopJumping();
}

// Called when the game starts or when spawned
void AProjectFaithCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectFaithCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AProjectFaithCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

