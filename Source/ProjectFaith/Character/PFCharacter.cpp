// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"

#include "Components/CapsuleComponent.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Player/PFPlayerController.h"

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
	
	
	
}

APFPlayerController* APFCharacter::GetPFPlayerController() const
{
	return CastChecked<APFPlayerController>(Controller, ECastCheckedType::NullAllowed);
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


// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

