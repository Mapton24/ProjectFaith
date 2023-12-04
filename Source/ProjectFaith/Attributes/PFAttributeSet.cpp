// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

UPFAttributeSet::UPFAttributeSet()
{
	InitMeleeLevel(1.f);
	InitRangedLevel(1.f);
}

void UPFAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetGiftAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxGift());
	}
	if (Attribute == GetMaxParryAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxParry());
	}
}

void UPFAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Combat Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeAttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedAttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeCritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedCritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeCritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedCritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeAttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedAttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeSkillDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedSkillDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, SynergyDamage, COND_None, REPNOTIFY_Always);
	//Rank Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MeleeRank, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, RangedRank, COND_None, REPNOTIFY_Always);
	//Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Gift, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxGift, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, Parry, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFAttributeSet, MaxParry, COND_None, REPNOTIFY_Always);
}


void UPFAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
	
}

void UPFAttributeSet::UpdateAttribute(const FGameplayAttribute& Attribute)
{
	if (Attribute == GetHealthAttribute()) SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	if (Attribute == GetManaAttribute()) SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	if (Attribute == GetGiftAttribute()) SetGift(FMath::Clamp(GetGift(), 0.f, GetMaxGift()));
	if (Attribute == GetParryAttribute()) SetParry(FMath::Clamp(GetParry(), 0.f, GetMaxParry()));
}
void UPFAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	UpdateAttribute(Data.EvaluatedData.Attribute);
}

UWorld* UPFAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);
	return Outer->GetWorld();
}


/*
 * Level Attributes
 */
void UPFAttributeSet::OnRep_MeleeLevel(const FGameplayAttributeData& OldMeleeLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeLevel, OldMeleeLevel);
}

void UPFAttributeSet::OnRep_RangedLevel(const FGameplayAttributeData& OldRangedLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedLevel, OldRangedLevel);
}
/*
 * Combat Attributes
 */
void UPFAttributeSet::OnRep_MeleeAttackDamage(const FGameplayAttributeData& OldMeleeAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeAttackDamage, OldMeleeAttackDamage);
}

void UPFAttributeSet::OnRep_RangedAttackDamage(const FGameplayAttributeData& OldRangedAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedAttackDamage, OldRangedAttackDamage);
}

void UPFAttributeSet::OnRep_MeleeCritChance(const FGameplayAttributeData& OldMeleeCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeCritChance, OldMeleeCritChance);
}

void UPFAttributeSet::OnRep_RangedCritChance(const FGameplayAttributeData& OldRangedCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedCritChance, OldRangedCritChance);

}

void UPFAttributeSet::OnRep_MeleeCritDamage(const FGameplayAttributeData& OldMeleeCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeCritDamage, OldMeleeCritDamage);
}

void UPFAttributeSet::OnRep_RangedCritDamage(const FGameplayAttributeData& OldRangedCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedCritDamage, OldRangedCritDamage);
}

void UPFAttributeSet::OnRep_MeleeAttackSpeed(const FGameplayAttributeData& OldMeleeAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeAttackSpeed, OldMeleeAttackSpeed);
}

void UPFAttributeSet::OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedAttackSpeed, OldRangedAttackSpeed);
}

void UPFAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UPFAttributeSet::OnRep_MeleeSkillDamage(const FGameplayAttributeData& OldMeleeSkillDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeSkillDamage, OldMeleeSkillDamage);
}

void UPFAttributeSet::OnRep_RangedSkillDamage(const FGameplayAttributeData& OldRangedSkillDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedSkillDamage, OldRangedSkillDamage);
}

void UPFAttributeSet::OnRep_SynergyDamage(const FGameplayAttributeData& OldSynergyDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, SynergyDamage, OldSynergyDamage);
}
/*
 * Rank Attributes
 */
void UPFAttributeSet::OnRep_MeleeRank(const FGameplayAttributeData& OldMeleeRank) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeRank, OldMeleeRank);
}

void UPFAttributeSet::OnRep_RangedRank(const FGameplayAttributeData& OldRangedRank) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedRank, OldRangedRank);
}
void UPFAttributeSet::OnRep_MeleeRankPotential(const FGameplayAttributeData& OldMeleeRankPotential) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, MeleeRankPotential, OldMeleeRankPotential);
}

void UPFAttributeSet::OnRep_RangedRankPotential(const FGameplayAttributeData& OldRangedRankPotential) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFAttributeSet, RangedRankPotential, OldRangedRankPotential);
}
/*
 * Vital Attributes
 */
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
