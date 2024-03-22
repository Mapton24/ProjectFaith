// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacterHero.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Player/PFPlayerController.h"
#include "ProjectFaith/Player/PFPlayerState.h"
#include "ProjectFaith/UI/HUD/PFHUD.h"

APFCharacterHero::APFCharacterHero()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom);
	
}

void APFCharacterHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void APFCharacterHero::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();

}

int32 APFCharacterHero::GetPlayerLevel()
{
	PFPlayerState = GetPlayerState<APFPlayerState>();
	check(PFPlayerState);
	return PFPlayerState->GetPlayerLevel();
}

void APFCharacterHero::InitAbilityActorInfo()
{
	PFPlayerState = GetPlayerState<APFPlayerState>();
	check(PFPlayerState);
	PFPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PFPlayerState, this);
	Cast<UPFAbilitySystemComponent>(PFPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = PFPlayerState->GetAbilitySystemComponent();
	AttributeSet = PFPlayerState->GetAttributeSet();

	if (APFPlayerController* PFPlayerController = Cast<APFPlayerController>(GetController()))
	{
		if (APFHUD* PFHUD = Cast<APFHUD>(PFPlayerController->GetHUD()))
		{
			PFHUD->InitOverlay(PFPlayerController, PFPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
	
}
