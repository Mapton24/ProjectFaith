// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PFPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API APFPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APFPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PF|PlayerState")
	UPFAbilitySystemComponent* GetPFAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	TObjectPtr<UPFAbilitySystemComponent> AbilitySystemComponent;
};

