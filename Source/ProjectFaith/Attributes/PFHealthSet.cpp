// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHealthSet.h"
#include "PFAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "GameplayEffectExtension.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PFHealthSet)

UPFHealthSet::UPFHealthSet()
	:Resource(100.0f)
    , MaxResource(100.0f)
{
}
void UPFHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPFHealthSet, Resource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPFHealthSet, MaxResource, COND_None, REPNOTIFY_Always);
}

void UPFHealthSet::OnRep_Resource(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFHealthSet, Resource, OldValue);
}

void UPFHealthSet::OnRep_MaxResource(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPFHealthSet, MaxResource, OldValue);
}

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
}

void UPFHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetResourceAttribute())
	{
		// Do not allow resource to go negative or above
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxResource());
	}
	else if (Attribute == GetMaxResourceAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
