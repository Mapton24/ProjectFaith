// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PFAttributeSet.generated.h"

class AActor;
class UObject;
class UWorld;
struct FGameplayEffectSpec;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UWorld* GetWorld() const override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gift, Category = "Gift")
	FGameplayAttributeData Gift;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Gift);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxGift, Category = "Gift")
	FGameplayAttributeData MaxGift;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxGift);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Parry, Category = "Parry")
	FGameplayAttributeData Parry;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, Parry);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxParry, Category = "Parry")
	FGameplayAttributeData MaxParry;
	ATTRIBUTE_ACCESSORS(UPFAttributeSet, MaxParry);

protected:
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
