// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_RangedSkillDamage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UMMC_RangedSkillDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_RangedSkillDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition RangedLevelDef;
	FGameplayEffectAttributeCaptureDefinition SynergyLevelDef;
};
