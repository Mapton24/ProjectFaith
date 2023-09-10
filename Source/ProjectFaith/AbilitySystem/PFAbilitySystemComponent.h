// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "Abilities/PFGameplayAbility.h"

#include "PFAbilitySystemComponent.generated.h"

class AActor;
/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UPFAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UPFAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	// Handles abilities that had input PRESSED this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	
	// Handles to abilities that had their input RELEASED this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that had their input HELD.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	// Number of abilities running in each activation group.
	
};
