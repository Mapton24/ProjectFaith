// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeMenuWidgetController.h"

#include "Chaos/Pair.h"
#include "ProjectFaith/PFGameplayTags.h"
#include "ProjectFaith/Attributes/PFAttributeSet.h"
#include "ProjectFaith/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UPFAttributeSet* AS = CastChecked<UPFAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AS](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FPFAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UPFAttributeSet* AS = CastChecked<UPFAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}
