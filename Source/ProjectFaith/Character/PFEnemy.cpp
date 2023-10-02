// Fill out your copyright notice in the Description page of Project Settings.


#include "PFEnemy.h"

#include "AbilitySystemComponent.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Attributes/PFAttributeSet.h"

APFEnemy::APFEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPFAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UPFAttributeSet>("AttributeSet");
	
}

void APFEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
