// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFGameplayAbility.h"
#include "PFProjectileSpell.generated.h"

class APFProjectile;
/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UPFProjectileSpell : public UPFGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		                         const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, bool isHoming);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APFProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
