// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PFGameplayAbility.generated.h"

/**
* PFActivationPolicy
* How an ability is meant to activate
*/
UENUM(BlueprintType)
enum class EPFAbilityActivationPolicy : uint8
{
	OnInputTriggered,

	WhileInputActive,

	OnSpawn
};
/**
 * 
 */
UENUM(BlueprintType)
enum class EPFAbilityActivationGroup : uint8
{
	//Ability runs independently
	Independent,

	//Ability is cancelled and replaced by other exlusive abilities.
	Exlusive_Replaceable,

	//Ability blocks all other exlusive abilities from activating.
	Exlusive_Blocking,

	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FPFAbilityMontageFailureMessage
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<APlayerController> PlayerController = nullptr;

		//The reasons why this ability has failed
		UPROPERTY(BlueprintReadWrite)
		FGameplayTagContainer FailureTags;
		UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UAnimMontage> FailureMontage = nullptr;

};



UCLASS(Abstract, HideCategories = Input, Meta = (ShortToolTip = "Base gameplay ability class used in this project."))
class PROJECTFAITH_API UPFGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UPFAbilitySystemComponent;

public:
	UPFGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PF|Ability")
	UPFAbilitySystemComponent* GetPFAbilitySystemComponentFromActorInfo() const;

	//UFUNCTION(BlueprintCallable, Category = "PF|Ability")
	

};
