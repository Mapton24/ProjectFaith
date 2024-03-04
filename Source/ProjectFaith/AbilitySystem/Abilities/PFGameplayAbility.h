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

	//Ability is cancelled and replaced by other exclusive abilities.
	Exclusive_Replaceable,

	//Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking,

	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FPFAbilityMontageFailureMessage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<APlayerController> PlayerController = nullptr;

		//The reasons why this ability has failed
		UPROPERTY(BlueprintReadWrite)
		FGameplayTagContainer FailureTags;
		UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UAnimMontage> FailureMontage = nullptr;

};


/**
 * UPFGameplayAbility
 *
 *	The base gameplay ability class used by this project.
 */
UCLASS()
class PROJECTFAITH_API UPFGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UPFAbilitySystemComponent;

public:
	UPFGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PF|Ability")
	UPFAbilitySystemComponent* GetPFAbilitySystemComponentFromActorInfo() const;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
	
	

};
