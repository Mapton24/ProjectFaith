// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * Singleton containing native Gmaeplay Tags
 */

struct FPFGameplayTags
{
	static const FPFGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Levels_MeleeLevel;
	FGameplayTag Attributes_Levels_RangedLevel;
	FGameplayTag Attributes_Levels_SynergyLevel;

	FGameplayTag Attributes_MeleeCombat_MeleeAttackDamage;
	FGameplayTag Attributes_MeleeCombat_MeleeCritChance;
	FGameplayTag Attributes_MeleeCombat_MeleeCritDamage;
	FGameplayTag Attributes_MeleeCombat_MeleeAttackSpeed;
	FGameplayTag Attributes_MeleeCombat_MeleeSkillDamage;

	FGameplayTag Attributes_RangedCombat_RangedAttackDamage;
	FGameplayTag Attributes_RangedCombat_RangedCritChance;
	FGameplayTag Attributes_RangedCombat_RangedCritDamage;
	FGameplayTag Attributes_RangedCombat_RangedAttackSpeed;
	FGameplayTag Attributes_RangedCombat_RangedSkillDamage;

	FGameplayTag Attributes_Synergy_SynergyDamage;
	FGameplayTag Attributes_Combat_MovementSpeed;
	
	FGameplayTag Attributes_Rank_MeleeRankPotential;
	FGameplayTag Attributes_Rank_RangedRankPotential;

private:
	static FPFGameplayTags GameplayTags;
};

namespace PFGameplayTags
{
	//TODO Create own tags
	PROJECTFAITH_API    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cooldown);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cost);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsBlocked);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsMissing);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Networking);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_ActivationGroup);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Reset);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_RequestReset);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_AutoRunning);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dying);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dead);

	PROJECTFAITH_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	PROJECTFAITH_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	PROJECTFAITH_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
}
