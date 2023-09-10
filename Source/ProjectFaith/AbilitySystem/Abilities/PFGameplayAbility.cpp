// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameplayAbility.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

UPFGameplayAbility::UPFGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPFAbilitySystemComponent* UPFGameplayAbility::GetPFAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UPFAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}
