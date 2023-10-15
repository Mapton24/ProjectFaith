// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAttributeSet.h"
#include "Net/UnrealNetwork.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

UPFAttributeSet::UPFAttributeSet()
{
	InitHealth(5.f);
	InitMaxHealth(100.f);
	InitMana(60.f);
	InitMaxMana(100.f);
	InitGift(70.f);
	InitMaxGift(100.f);
	InitParry(80.f);
	InitMaxParry(100.f);
}

void UPFAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Gift, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxGift, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Parry, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxParry, COND_None, REPNOTIFY_Always);

}

UWorld* UPFAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);
	return Outer->GetWorld();
}

void UPFAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, Health, OldHealth);
}

void UPFAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MaxHealth, OldMaxHealth);
}

void UPFAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, Mana, OldMana);
}

void UPFAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MaxMana, OldMaxMana);
}

void UPFAttributeSet::OnRep_Gift(const FGameplayAttributeData& OldGift) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, Gift, OldGift);
}

void UPFAttributeSet::OnRep_MaxGift(const FGameplayAttributeData& OldMaxGift) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MaxGift, OldMaxGift);
}

void UPFAttributeSet::OnRep_Parry(const FGameplayAttributeData& OldParry) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, Parry, OldParry);
}

void UPFAttributeSet::OnRep_MaxParry(const FGameplayAttributeData& OldMaxParry) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MaxParry, OldMaxParry);
}
