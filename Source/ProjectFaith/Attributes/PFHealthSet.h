// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "PFAttributeSet.h"
#include "NativeGameplayTags.h"

#include "PFHealthSet.generated.h"

class UObject;
struct FFrame;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_PF_Damage_Message);

struct FGameplayEffectModCallbackData;
/**
 * Class that defines attributes necessary for damage.
 */
UCLASS()
class PROJECTFAITH_API UPFHealthSet : public UPFAttributeSet
{
	GENERATED_BODY()

public:
	UPFHealthSet();

	ATTRIBUTE_ACCESSORS(UPFHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UPFHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UPFHealthSet, Healing);
	ATTRIBUTE_ACCESSORS(UPFHealthSet, Damage);

	mutable FLyraAttributeEvent OnOutOfHealth;

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	//The current health attribute.  The health will be capped by the max health attribute.  Health is hidden from modifiers so only executions can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "PF|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "PF|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	// Tracks if health reaches 0
	bool bOutOfHealth;

private:
	// Incoming healing. This is mapped directly to +Health
	UPROPERTY(BlueprintReadOnly, Category="PF|Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category="PF|Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
};
