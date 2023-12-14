// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_RangedSkillDamage.h"

#include "ProjectFaith/Attributes/PFAttributeSet.h"

UMMC_RangedSkillDamage::UMMC_RangedSkillDamage()
{
	RangedLevelDef.AttributeToCapture = UPFAttributeSet::GetMeleeLevelAttribute();
	RangedLevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	RangedLevelDef.bSnapshot = false;
	SynergyLevelDef.AttributeToCapture = UPFAttributeSet::GetRangedLevelAttribute();
	SynergyLevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SynergyLevelDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(RangedLevelDef);
	RelevantAttributesToCapture.Add(SynergyLevelDef);
}

float UMMC_RangedSkillDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float RangedLevel = 0.f;
	GetCapturedAttributeMagnitude(RangedLevelDef, Spec, EvaluationParameters, RangedLevel);
	RangedLevel = FMath::Max<float>(RangedLevel, 0.f);

	float SynergyLevel = 0.f;
	GetCapturedAttributeMagnitude(SynergyLevelDef, Spec, EvaluationParameters, SynergyLevel);
	SynergyLevel = FMath::Max<float>(RangedLevel, 0.f);

	return RangedLevel + SynergyLevel * 0.5f; 
	
}