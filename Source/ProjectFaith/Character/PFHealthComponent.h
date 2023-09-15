// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/GameFrameworkComponent.h"
#include "PFHealthComponent.generated.h"

class UPFAbilitySystemComponent;
class UPFHealthSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FPFHealth_AttributeChanged, UPFHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPFHealth_DeathEvent, AActor*, OwningActor);



/**
 *
 * Defines current state of death.
 */
UENUM(BlueprintType)
enum class EPFDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};
/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UPFHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UPFHealthComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "PF|Health")
	static UPFHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UPFHealthComponent>() : nullptr);}

	UFUNCTION(BlueprintCallable, Category = "PF|Health")
	void InitializeWithAbilitySystem(UPFAbilitySystemComponent * InASC);

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "PF|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category= "PF|Health")
	float GetMaxHealth() const;

	//Begins the death sequence for the owner.
	virtual void StartDeath();

	//End the death sequence for the owner.
	virtual void FinishState();


	

public:

	//Delegate fired when the health value is changed.
	UPROPERTY(BlueprintAssignable)
	FPFHealth_AttributeChanged OnHealthChanged;
	
	//Delegate fired when the max health value is changed.
	UPROPERTY(BlueprintAssignable)
	FPFHealth_AttributeChanged OnMaxHealthChanged;

	//Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FPFHealth_DeathEvent OnDeathStarted;
	
	//Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FPFHealth_DeathEvent OnDeathFinished;
	

	

	

	
protected:

	void ClearGameplayTags();
	
	virtual void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);

	UFUNCTION()
	virtual void OnRep_DeathState(EPFDeathState OldDeathState);


protected:

	// Ability system used by this component
	UPROPERTY()
	TObjectPtr<UPFAbilitySystemComponent> AbilitySystemComponent;
	
    // HealthSet used by this component
	UPROPERTY()
	TObjectPtr<const UPFHealthSet> HealthSet;

	//Replicated state used to handle dying.
	UPROPERTY(ReplicatedUsing = OnRep_DeathState)
	EPFDeathState DeathState;

	
	
	
};
