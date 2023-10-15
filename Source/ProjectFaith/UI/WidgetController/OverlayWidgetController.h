// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "PFWidgetController.h"
#include "OverlayWidgetController.generated.h"



struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGiftChangedSignature, float, NewGift);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxGiftChangedSignature, float, NewMaxGift);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParryChangedSignature, float, NewParry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxParryChangedSignature, float, NewMaxParry);

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UOverlayWidgetController : public UPFWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGiftChangedSignature OnGiftChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxGiftChangedSignature OnMaxGiftChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnParryChangedSignature OnParryChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxParryChangedSignature OnMaxParryChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	void GiftChanged(const FOnAttributeChangeData& Data) const;
	void MaxGiftChanged(const FOnAttributeChangeData& Data) const;
	void ParryChanged(const FOnAttributeChangeData& Data) const;
	void MaxParryChanged(const FOnAttributeChangeData& Data) const;
};
