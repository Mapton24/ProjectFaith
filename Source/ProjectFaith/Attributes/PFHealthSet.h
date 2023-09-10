// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "PFAttributeSet.h"
#include "NativeGameplayTags.h"

#include "PFHealthSet.generated.h"

class UObject;
struct FFrame;

struct FGameplayEffectModCallbackData;
/**
 * A base class for classes that use resources like health, mana, stamina etc.
 */
UCLASS()
class PROJECTFAITH_API UPFHealthSet : public UPFAttributeSet
{
	GENERATED_BODY()

public:
	UPFHealthSet();

	 ATTRIBUTE_ACCESSORS(UPFHealthSet, Resource);
	 ATTRIBUTE_ACCESSORS(UPFHealthSet, MaxResource);

	mutable FLyraAttributeEvent OnOutOfResource;

protected:
	UFUNCTION()
	virtual void OnRep_Resource(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxResource(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resource, Category = "PF|Resource", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Resource;
	
	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxResource, Category = "PF|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxResource;
	
};
