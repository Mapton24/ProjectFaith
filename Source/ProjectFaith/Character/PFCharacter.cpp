// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"

#include "PFCharacterMovementComponent.h"
#include "PFHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectFaith/PFGameplayTags.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

// Sets default values

static FName NAME_PFCharacterCollisionProfile_Capsule(TEXT("PFPawnCapsule"));


APFCharacter::APFCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComp->SetCollisionProfileName(NAME_PFCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComponent = GetMesh();
	check(MeshComponent);
	FVector NewLocation = MeshComponent->GetComponentLocation();
	NewLocation.Z = -88.00f;
	MeshComponent->SetWorldLocation(NewLocation);

	HealthComponent = CreateDefaultSubobject<UPFHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
}

UPFAbilitySystemComponent* APFCharacter::GetPFAbilitySystemComponent() const
{
	return Cast<UPFAbilitySystemComponent>(GetAbilitySystemComponent());
}
UAbilitySystemComponent* APFCharacter::GetAbilitySystemComponent() const
{
	//TODO Might crash whole game
	return GetAbilitySystemComponent();
}

void APFCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		PFASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool APFCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		return PFASC->HasMatchingGameplayTag(TagToCheck);
	}
	return false;
}

bool APFCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		return PFASC->HasAllMatchingGameplayTags(TagContainer);
	}
	return false;
}

bool APFCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		return PFASC->HasAnyMatchingGameplayTags(TagContainer);
	}
	return false;
}

void APFCharacter::ToggleCrouch()
{
	const UPFCharacterMovementComponent* PFMoveComp = CastChecked<UPFCharacterMovementComponent>(GetCharacterMovement());

	if (bIsCrouched || PFMoveComp->bWantsToCrouch)
	{
		UnCrouch();
	} else if (PFMoveComp->IsMovingOnGround())
	{
		Crouch();
	}
}

void APFCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void APFCharacter::Reset()
{
	
}

void APFCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void APFCharacter::OnAbiltySystemInitialized()
{
	UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent();
	check(PFASC);

	HealthComponent->InitializeWithAbilitySystem(PFASC);

	InitializeGameplayTags();
}

// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APFCharacter::InitializeGameplayTags()
{
	//Clear tags that might be lingering on the ability system from the previous pawn.
	if (UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		for (const TPair<uint8, FGameplayTag>& TagMapping : PFGameplayTags::MovementModeTagMap)
		{
			if(TagMapping.Value.IsValid())
			{
				PFASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}
		for (const TPair<uint8, FGameplayTag> TagMapping : PFGameplayTags::CustomMovementModeTagMap)
		{
			if(TagMapping.Value.IsValid())
			{
				PFASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}
		UPFCharacterMovementComponent* PFMoveComp = CastChecked<UPFCharacterMovementComponent>(GetCharacterMovement());
		//TODO SetMovementModeTag
	}
	
}

void APFCharacter::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();
}

void APFCharacter::OnDeathFinished(AActor* OwningActor)
{
	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void APFCharacter::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToChannels(ECR_Ignore);

	UPFCharacterMovementComponent* PFMoveComp = CastChecked<UPFCharacterMovementComponent>(GetCharacterMovement());
	check(PFMoveComp);
	PFMoveComp->StopMovementImmediately();
	PFMoveComp->DisableMovement();
}

void APFCharacter::DestroyDueToDeath()
{
	K2_OnDeathFinished();
	UninitAndDestroy();
}

void APFCharacter::UninitAndDestroy()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(0.1f);
	}
	SetActorHiddenInGame(true);
}


