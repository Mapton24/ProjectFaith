// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerState.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"


APFPlayerState::APFPlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UPFAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* APFPlayerState::GetAbilitySystemComponent() const
{
	return GetPFAbilitySystemComponent();
}
