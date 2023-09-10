// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "ProjectFaith/Player/PFLocalPlayer.h"

UPFInputComponent::UPFInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UPFInputComponent::AddInputMappings(const UPFInputConfig* InputConfig,
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem)

	UPFLocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<UPFLocalPlayer>();
	check(LocalPlayer);
	//TODO Add SettingsLocal to finish
}

void UPFInputComponent::RemoveInputMappings(const UPFInputConfig* InputConfig,
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	UPFLocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<UPFLocalPlayer>();
	check(LocalPlayer);
}

