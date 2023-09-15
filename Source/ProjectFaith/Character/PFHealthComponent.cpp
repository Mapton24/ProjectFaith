// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHealthComponent.h"

#include "GameplayEffectExtension.h"
#include "GameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "ProjectFaith/PFGameplayTags.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Attributes/PFHealthSet.h"

UPFHealthComponent::UPFHealthComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UPFHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPFHealthComponent, DeathState);
}

void UPFHealthComponent::InitializeWithAbilitySystem(UPFAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		//TODO create log system - Health component has already been initialized
		return;
	}
	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		//TODO create log system - Health component can't be initialize on null
		return;
	}
	HealthSet = AbilitySystemComponent->GetSet<UPFHealthSet>();
	if (!HealthSet)
	{
		//TODO create log system - Health component can't be intialized if HealthSet is null
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPFHealthSet::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	

	
}

float UPFHealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);
}

float UPFHealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);
}

void UPFHealthComponent::StartDeath()
{
}

void UPFHealthComponent::FinishState()
{
}

void UPFHealthComponent::OnRep_DeathState(EPFDeathState OldDeathState)
{
	const EPFDeathState NewDeathState = DeathState;

	// Revert the death state for now since we rely on StartDeath and FinishDeath to change it.
	DeathState = OldDeathState;

	if (OldDeathState > NewDeathState)
	{
		//TODO create logging system
		return;
	}

	if (OldDeathState == EPFDeathState::NotDead)
	{
		if (NewDeathState == EPFDeathState::DeathStarted)
		{
			StartDeath();
		}
	}

	
}

static AActor* GetInstigatorFromAttrChangeData(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.GEModData != nullptr)
	{
		const FGameplayEffectContextHandle& EffectContext = ChangeData.GEModData->EffectSpec.GetEffectContext();
		return EffectContext.GetOriginalInstigator();
	}
	return nullptr;
}
void UPFHealthComponent::HandleHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}
void UPFHealthComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}

void UPFHealthComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dying, 0);
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dead, 0);
	}
}


