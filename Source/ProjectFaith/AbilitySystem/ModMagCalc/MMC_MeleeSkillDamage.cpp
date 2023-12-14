// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_MeleeSkillDamage.h"

#include "ProjectFaith/Attributes/PFAttributeSet.h"


UMMC_MeleeSkillDamage::UMMC_MeleeSkillDamage()
{
	MeleeLevelDef.AttributeToCapture = UPFAttributeSet::GetMeleeLevelAttribute();
	MeleeLevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MeleeLevelDef.bSnapshot = false;
	SynergyLevelDef.AttributeToCapture = UPFAttributeSet::GetRangedLevelAttribute();
	SynergyLevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SynergyLevelDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(MeleeLevelDef);
	RelevantAttributesToCapture.Add(SynergyLevelDef);
}

float UMMC_MeleeSkillDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float MeleeLevel = 0.f;
	GetCapturedAttributeMagnitude(MeleeLevelDef, Spec, EvaluationParameters, MeleeLevel);
	MeleeLevel = FMath::Max<float>(MeleeLevel, 0.f);

	float SynergyLevel = 0.f;
	GetCapturedAttributeMagnitude(SynergyLevelDef, Spec, EvaluationParameters, SynergyLevel);
	SynergyLevel = FMath::Max<float>(MeleeLevel, 0.f);

	return MeleeLevel + SynergyLevel * 0.5f; 
	
}


