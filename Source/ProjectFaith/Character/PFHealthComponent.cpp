// Fill out your copyright notice in the Description page of Project Settings.
// TODO THIS CLASS WILL BE USABLE AFTER I LEARN MORE ABOUT ASC CALCULATIONS

#include "PFHealthComponent.h"

#include "ProjectFaith/PFLogChannels.h"
#include "GameplayEffectExtension.h"
#include "ProjectFaith/PFGameplayTags.h"
#include "Net/UnrealNetwork.h"
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
		UE_LOG(LogPF, Error, TEXT("PFHealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}
	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogPF, Error, TEXT("PFHealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}
	HealthSet = AbilitySystemComponent->GetSet<UPFHealthSet>();
	if (!HealthSet)
	{
		UE_LOG(LogPF, Error, TEXT("PFHealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPFHealthSet::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPFHealthSet::GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);


	// Reset attributes to default values.
	AbilitySystemComponent->SetNumericAttributeBase(UPFHealthSet::GetHealthAttribute(), HealthSet->GetMaxHealth());

	ClearGameplayTags();

	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetMaxHealth(), HealthSet->GetMaxHealth(), nullptr);
}

float UPFHealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);
}

float UPFHealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);
}

float UPFHealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();

		return ((MaxHealth > 0.0f) ? (Health/MaxHealth) : 0.0f);
	}
	return 0.0f;
}

void UPFHealthComponent::StartDeath()
{
	if (DeathState != EPFDeathState::NotDead)
	{
		return;
	}

	DeathState = EPFDeathState::DeathStarted;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dying, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathStarted.Broadcast(Owner);
}

void UPFHealthComponent::FinishDeath()
{
	if (DeathState != EPFDeathState::DeathStarted)
	{
		return;
	}

	DeathState = EPFDeathState::DeathFinished;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dead, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathFinished.Broadcast(Owner);

	Owner->ForceNetUpdate();
	
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

void UPFHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{

	//GameplayEvent.Death - can be used to trigger death gameplay ability.
	if (AbilitySystemComponent)
	{
		FGameplayEventData Payload;
		Payload.EventTag = PFGameplayTags::GameplayEvent_Death;
		Payload.Instigator = DamageInstigator;
		Payload.Target = AbilitySystemComponent->GetAvatarActor();
		Payload.OptionalObject = DamageEffectSpec.Def;
		Payload.ContextHandle = DamageEffectSpec.GetEffectContext();
		Payload.InstigatorTags = *DamageEffectSpec.CapturedSourceTags.GetAggregatedTags();
		Payload.TargetTags = *DamageEffectSpec.CapturedTargetTags.GetAggregatedTags();
		Payload.EventMagnitude = DamageMagnitude;

		FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
		AbilitySystemComponent->HandleGameplayEvent(Payload.EventTag, &Payload);
	}
}

void UPFHealthComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dying, 0);
		AbilitySystemComponent->SetLooseGameplayTagCount(PFGameplayTags::Status_Death_Dead, 0);
	}
}


