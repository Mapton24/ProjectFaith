// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"
#include "ProjectFaith/Attributes/PFAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UPFAttributeSet* PFAttributeSet = CastChecked<UPFAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(PFAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(PFAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(PFAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(PFAttributeSet->GetMaxMana());
	OnGiftChanged.Broadcast(PFAttributeSet->GetGift());
	OnMaxGiftChanged.Broadcast(PFAttributeSet->GetMaxGift());
	OnParryChanged.Broadcast(PFAttributeSet->GetParry());
	OnMaxParryChanged.Broadcast(PFAttributeSet->GetMaxParry());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPFAttributeSet* PFAttributeSet = CastChecked<UPFAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetGiftAttribute()).AddUObject(this, &UOverlayWidgetController::GiftChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxGiftAttribute()).AddUObject(this, &UOverlayWidgetController::MaxGiftChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetParryAttribute()).AddUObject(this, &UOverlayWidgetController::ParryChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxParryAttribute()).AddUObject(this, &UOverlayWidgetController::MaxParryChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::GiftChanged(const FOnAttributeChangeData& Data) const
{
	OnGiftChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxGiftChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxGiftChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ParryChanged(const FOnAttributeChangeData& Data) const
{
	OnParryChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxParryChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxParryChanged.Broadcast(Data.NewValue);
}
