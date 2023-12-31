// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInputConfig.h"

UPFInputConfig::UPFInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UPFInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FPFInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		
	}
	return nullptr;
}

const UInputAction* UPFInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FPFInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
	}
	return nullptr;
}
