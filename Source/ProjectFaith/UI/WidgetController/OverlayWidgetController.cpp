// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "ProjectFaith/Attributes/PFAttributeSet.h"
#include "ProjectFaith/Messages/PFNotificationMessage.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PFAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PFAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetGiftAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnGiftChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxGiftAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxGiftChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetParryAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnParryChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PFAttributeSet->GetMaxParryAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxParryChanged.Broadcast(Data.NewValue);
			});

	Cast <UPFAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FPFNotificationMessage* Row = GetDataTableRowByTag<FPFNotificationMessage>(MessageWidgetDataTable, Tag);
					if (Row)
					{
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		});
}
