// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAttributeSet.h"

#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"

UPFAttributeSet::UPFAttributeSet()
{
}

UWorld* UPFAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
	
}

UPFAbilitySystemComponent* UPFAttributeSet::GetPFAbilitySystemComponent() const
{
	return Cast<UPFAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
