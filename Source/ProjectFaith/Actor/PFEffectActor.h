// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "PFEffectActor.generated.h"

class USphereComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class PROJECTFAITH_API APFEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APFEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantGameplayEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationGameplayEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteGameplayEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f; 
};
