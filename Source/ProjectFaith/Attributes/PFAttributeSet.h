// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "PFAttributeSet.generated.h"

class AActor;
class UObject;
class UWorld;
struct FGameplayEffectSpec;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * This macro defines a set of helper functions for accessing and initializing attributes.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Delegate used to broadcast attribute events.
DECLARE_MULTICAST_DELEGATE_FourParams(FLyraAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec& /*EffectSpec*/, float /*EffectMagnitude*/);

/**
 * Base attribute set class for this project
 */
UCLASS()
class PROJECTFAITH_API UPFAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPFAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void UpdateAttribute(const FGameplayAttribute& Attribute);
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	UWorld* GetWorld() const override;


	/*
	 * Level Attribute
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeLevel, Category = "Level Attributes")
	FGameplayAttributeData MeleeLevel;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeLevel);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedLevel, Category = "Level Attributes")
	FGameplayAttributeData RangedLevel;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedLevel);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SynergyLevel, Category = "Level Attributes")
	FGameplayAttributeData SynergyLevel;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, SynergyLevel);
	
	/*
	 * Combat Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeAttackDamage, Category = "Melee Combat Attributes")
	FGameplayAttributeData MeleeAttackDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeAttackDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeCritChance, Category = "Melee Combat Attributes")
	FGameplayAttributeData MeleeCritChance;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeCritChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeCritDamage, Category = "Melee Combat Attributes")
	FGameplayAttributeData MeleeCritDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeCritDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeAttackSpeed, Category = "Melee Combat Attributes")
	FGameplayAttributeData MeleeAttackSpeed;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeAttackSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeSkillDamage, Category = "Melee Combat Attributes")
	FGameplayAttributeData MeleeSkillDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeSkillDamage);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedAttackDamage, Category = "Ranged Combat Attributes")
	FGameplayAttributeData RangedAttackDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedAttackDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedCritChance, Category = "Ranged Combat Attributes")
	FGameplayAttributeData RangedCritChance;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedCritChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedCritDamage, Category = "Ranged Combat Attributes")
	FGameplayAttributeData RangedCritDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedCritDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedAttackSpeed, Category = "Ranged Combat Attributes")
	FGameplayAttributeData RangedAttackSpeed;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedAttackSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedSkillDamage, Category = "Ranged Combat Attributes")
	FGameplayAttributeData RangedSkillDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedSkillDamage);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SynergyDamage, Category = "Combat Attributes")
	FGameplayAttributeData SynergyDamage;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, SynergyDamage);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Combat Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MovementSpeed);
	
	/*
	 * Rank Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeRank, Category = "Rank Attributes")
	FGameplayAttributeData MeleeRank;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeRank);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedRank, Category = "Rank Attributes")
	FGameplayAttributeData RangedRank;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedRank);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeRankPotential, Category = "Rank Attributes")
	FGameplayAttributeData MeleeRankPotential;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MeleeRankPotential);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedRankPotential, Category = "Rank Attributes")
	FGameplayAttributeData RangedRankPotential;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, RangedRankPotential);

	/*
	 * Vital Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Max Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Max Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gift, Category = "Vital Attributes")
	FGameplayAttributeData Gift;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Gift);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxGift, Category = "Max Vital Attributes")
	FGameplayAttributeData MaxGift;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxGift);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Parry, Category = "Vital Attributes")
	FGameplayAttributeData Parry;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Parry);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxParry, Category = "Max Vital Attributes")
	FGameplayAttributeData MaxParry;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxParry);

private:
	void SetEffectProperties( const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

	
protected:
	//Level OnRep
	UFUNCTION()
	void OnRep_MeleeLevel(const FGameplayAttributeData& OldMeleeLevel) const;
	UFUNCTION()
	void OnRep_RangedLevel(const FGameplayAttributeData& OldRangedLevel) const;
	UFUNCTION()
	void OnRep_SynergyLevel(const FGameplayAttributeData& OldSynergyLevel) const;
	//Combat OnRep
	UFUNCTION()
	void OnRep_MeleeAttackDamage(const FGameplayAttributeData& OldMeleeAttackDamage) const;
	UFUNCTION()
	void OnRep_RangedAttackDamage(const FGameplayAttributeData& OldRangedAttackDamage) const;
	UFUNCTION()
	void OnRep_MeleeCritChance(const FGameplayAttributeData& OldMeleeCritChance) const;
	UFUNCTION()
	void OnRep_RangedCritChance(const FGameplayAttributeData& OldRangedCritChance) const;
	UFUNCTION()
	void OnRep_MeleeCritDamage(const FGameplayAttributeData& OldMeleeCritDamage) const;
	UFUNCTION()
	void OnRep_RangedCritDamage(const FGameplayAttributeData& OldRangedCritDamage) const;
	UFUNCTION()
	void OnRep_MeleeAttackSpeed(const FGameplayAttributeData& OldMeleeAttackSpeed) const;
	UFUNCTION()
	void OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed) const;
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	UFUNCTION()
	void OnRep_MeleeSkillDamage(const FGameplayAttributeData& OldMeleeSkillDamage) const;
	UFUNCTION()
	void OnRep_RangedSkillDamage(const FGameplayAttributeData& OldRangedSkillDamage) const;
	UFUNCTION()
	void OnRep_SynergyDamage(const FGameplayAttributeData& OldSynergyDamage) const;
	//Rank OnRep
	UFUNCTION()
	void OnRep_MeleeRank(const FGameplayAttributeData& OldMeleeRank) const;
	UFUNCTION()
	void OnRep_RangedRank(const FGameplayAttributeData& OldRangedRank) const;
	UFUNCTION()
	void OnRep_MeleeRankPotential(const FGameplayAttributeData& OldMeleeRankPotential) const;
	UFUNCTION()
	void OnRep_RangedRankPotential(const FGameplayAttributeData& OldRangedRankPotential) const;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Gift(const FGameplayAttributeData& OldGift) const;
	UFUNCTION()
	void OnRep_MaxGift(const FGameplayAttributeData& OldMaxGift) const;
	UFUNCTION()
	void OnRep_Parry(const FGameplayAttributeData& OldParry) const;
	UFUNCTION()
	void OnRep_MaxParry(const FGameplayAttributeData& OldMaxParry) const;
	
};
