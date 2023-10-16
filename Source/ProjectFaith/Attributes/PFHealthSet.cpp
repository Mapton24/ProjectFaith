// Fill out your copyright notice in the Description page of Project Settings.
// TODO THIS CLASS WILL BE USABLE AFTER I LEARN MORE ABOUT ASC CALCULATIONS


#include "PFHealthSet.h"
#include "PFAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "GameplayEffectExtension.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PFHealthSet)

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Damage, "Gameplay.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageImmunity, "Gameplay.DamageImmunity")
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_FellOutOfWorld, "Gameplay.Damage.FellOutOfWorld")
UE_DEFINE_GAMEPLAY_TAG(Tag_PF_Damage_Message, "PF.Damage.Message");


UPFHealthSet::UPFHealthSet()
	// : Health(100.0f)
 //    , MaxHealth(100.0f)
{
	bOutOfHealth = false;
}
// void UPFHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
// 	DOREPLIFETIME_CONDITION_NOTIFY(UPFHealthSet, Health, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UPFHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
// }
//
// void UPFHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFHealthSet, Health, OldValue);
// }
//
// void UPFHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFHealthSet, MaxHealth, OldValue);
// }

void UPFHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UPFHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UPFHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		if (GetHealth() > NewValue)
		{
			// UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent();
			// check(PFASC);
			//
			// PFASC->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}
	if (bOutOfHealth && (GetHealth() > 0.0f))
	{
		bOutOfHealth = false;
	}
}

void UPFHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		// Do not allow resource to go negative or above
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
