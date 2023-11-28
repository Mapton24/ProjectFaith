// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacterMain.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Player/PFPlayerController.h"
#include "ProjectFaith/Player/PFPlayerState.h"
#include "ProjectFaith/UI/HUD/PFHUD.h"

APFCharacterMain::APFCharacterMain()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom);
	
}

void APFCharacterMain::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void APFCharacterMain::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();

}

void APFCharacterMain::InitAbilityActorInfo()
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
	
}
