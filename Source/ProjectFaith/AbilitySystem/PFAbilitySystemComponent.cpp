// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAbilitySystemComponent.h"

#include "Abilities/PFGameplayAbility.h"
#include "GameFramework/Pawn.h"


void UPFAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UPFAbilitySystemComponent::EffectApplied);
}

UPFAbilitySystemComponent::UPFAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UPFAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
