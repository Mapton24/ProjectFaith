// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

namespace PFCharacter
{
	static float GroundTraceDistance = 100000.0f;
	FAutoConsoleVariableRef CVarRef_GroundTraceDistance(TEXT("PFCharacter.GroundTraceDistance"), GroundTraceDistance, TEXT("Distance to trace down when generating ground information."), ECVF_Cheat);
}

UPFCharacterMovementComponent::UPFCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPFCharacterMovementComponent::SimulateMovement(float DeltaTime)
{
	Super::SimulateMovement(DeltaTime);
}

bool UPFCharacterMovementComponent::CanAttemptJump() const
{
	return IsJumpAllowed() &&
		(IsMovingOnGround() || IsFalling());
}

void UPFCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

const FPFCharacterGroundInfo& UPFCharacterMovementComponent::GetGroundInfo()
{
	if(!CharacterOwner || (GFrameCounter == CachedGroundInfo.LastUpdateFrame))
	{
		return CachedGroundInfo;
	}
	if (MovementMode == MOVE_Walking)
	{
		CachedGroundInfo.GroundHitResult = CurrentFloor.HitResult;
		CachedGroundInfo.GroundDistance = 0.0f;
	}
	else
	{
		const UCapsuleComponent* CapsuleComp = CharacterOwner->GetCapsuleComponent();
		check(CapsuleComp);

		const float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();
		const ECollisionChannel CollisionChannel = (UpdatedComponent ? UpdatedComponent->GetCollisionObjectType() : ECC_Pawn);
		const FVector TraceStart(GetActorLocation());
		const FVector TraceEnd(TraceStart.X, TraceStart.Y, (TraceStart.Z - PFCharacter::GroundTraceDistance - CapsuleHalfHeight));

		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(LyraCharacterMovementComponent_GetGroundInfo), false, CharacterOwner);
		FCollisionResponseParams ResponseParam;
		InitCollisionParams(QueryParams, ResponseParam);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, QueryParams, ResponseParam);

		CachedGroundInfo.GroundHitResult = HitResult;
		CachedGroundInfo.GroundDistance = PFCharacter::GroundTraceDistance;
	}
	CachedGroundInfo.LastUpdateFrame = GFrameCounter;
	return CachedGroundInfo;
}


	


