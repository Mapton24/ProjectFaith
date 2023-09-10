// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAbilitySystemComponent.h"

#include "Abilities/PFGameplayAbility.h"
#include "GameFramework/Pawn.h"

UPFAbilitySystemComponent::UPFAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}
