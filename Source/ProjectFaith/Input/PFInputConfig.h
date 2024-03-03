// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PFInputConfig.generated.h"


/**
 * FPFInputAction
 *
 * Struct used to map input action to gameplay input tag.
 */

USTRUCT(BlueprintType)
struct FPFInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
UCLASS()
class PROJECTFAITH_API UPFInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPFInputConfig(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category= "PF|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	
	//List of input actions used by the owner. These inputs actions are mapped to a gameplay tag that must be bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FPFInputAction> NativeInputActions;
	//List of input actions used by the owner. These inputs actions are mapped to a gameplay tag and are automatically bound to abilities witch matching input tags.

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPFInputAction> AbilityInputActions;
	

	
	
	
};
