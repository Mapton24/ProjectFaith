// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameplayTags.h"

#include "AssetTypeCategories.h"

FPFGameplayTags FPFGameplayTags::GameplayTags;

void FPFGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Level Attributes
	 */
	
	GameplayTags.Attributes_Levels_MeleeLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Levels.MeleeLevel"),
		FString("PC level.")
		);

	GameplayTags.Attributes_Levels_RangedLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Levels.RangedLevel"),
		FString("Mima level.")
		);

	GameplayTags.Attributes_Levels_SynergyLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Levels.SynergyLevel"),
		FString("PC and Mima synergy level.")
		);

	/*
	 * Melee Combat Attributes
	 */

	GameplayTags.Attributes_MeleeCombat_MeleeAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MeleeCombat.MeleeAttackDamage"),
		FString("Increases PC physical damage.")
		);
	
	GameplayTags.Attributes_MeleeCombat_MeleeCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MeleeCombat.MeleeCritChance"),
		FString("Increases PC chance to hit hard.")
		);

	GameplayTags.Attributes_MeleeCombat_MeleeCritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MeleeCombat.MeleeCritDamage"),
		FString("Increases PC weak point damage.")
		);

	GameplayTags.Attributes_MeleeCombat_MeleeAttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MeleeCombat.MeleeAttackSpeed"),
		FString("Increases PC attack speed.")
		);

	GameplayTags.Attributes_MeleeCombat_MeleeSkillDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MeleeCombat.MeleeSkillDamage"),
		FString("Increases PC special skill damage.")
		);
	/*
	 * Ranged Combat Attributes
	 */

	GameplayTags.Attributes_RangedCombat_RangedAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.RangedCombat.RangedAttackDamage"),
		FString("Increases Mima magical damage.")
		);
	
	GameplayTags.Attributes_RangedCombat_RangedCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.RangedCombat.RangedCritChance"),
		FString("Increases Mima chance to hit hard.")
		);

	GameplayTags.Attributes_RangedCombat_RangedCritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.RangedCombat.RangedCritDamage"),
		FString("Increases Mima weak point damage.")
		);

	GameplayTags.Attributes_RangedCombat_RangedAttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.RangedCombat.RangedAttackSpeed"),
		FString("Increases Mima casting speed.")
		);

	GameplayTags.Attributes_RangedCombat_RangedSkillDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.RangedCombat.RangedSkillDamage"),
		FString("Increases Mima special skill damage.")
		);

	/*
	 * Synergy
	 */

	GameplayTags.Attributes_Synergy_SynergyDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Synergy.SynergyDamage"),
		FString("Increases heroes combined Synergy Damage.")
		);

	/*
	 * Miscellaneous
	 */

	GameplayTags.Attributes_Combat_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Combat.MovementSpeed"),
		FString("Increases heroes movement speed.")
		);

	/*
	 * Rank
	 */

	GameplayTags.Attributes_Rank_MeleeRankPotential = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Rank.MeleeRankPotential"),
	FString("Increases PC ability to increase his rank.")
	);
	GameplayTags.Attributes_Rank_RangedRankPotential = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Combat.RangedRankPotential"),
	FString("Increases Mima ability to increase her rank.")
	);

	/*
	 * Max Vitals
	 */
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxHealth"),
	FString("PC max health.")
	);
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxMana"),
	FString("Mima max mana.")
	);
	GameplayTags.Attributes_Vital_MaxGift = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxGift"),
	FString("PC max gift.")
	);
	GameplayTags.Attributes_Vital_MaxParry = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxParry"),
	FString("PC max parry.")
	);
	
}

namespace PFGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_IsDead, "Ability.ActivateFail.IsDead", "Ability failed to activate because its owner is dead.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Cooldown, "Ability.ActivateFail.Cooldown", "Ability failed to activate because it is on cool down.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Cost, "Ability.ActivateFail.Cost", "Ability failed to activate because it did not pass the cost checks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_TagsBlocked, "Ability.ActivateFail.TagsBlocked", "Ability failed to activate because tags are blocking it.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_TagsMissing, "Ability.ActivateFail.TagsMissing", "Ability failed to activate because tags are missing.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Networking, "Ability.ActivateFail.Networking", "Ability failed to activate because it did not pass the network checks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_ActivationGroup, "Ability.ActivateFail.ActivationGroup", "Ability failed to activate because of its activation group.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Behavior_SurvivesDeath, "Ability.Behavior.SurvivesDeath", "An ability with this type tag should not be canceled due to death.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Crouch, "InputTag.Crouch", "Crouch input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_AutoRun, "InputTag.AutoRun", "Auto-run input.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_Spawned, "InitState.Spawned", "1: Actor/component has initially spawned and can be extended");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataAvailable, "InitState.DataAvailable", "2: All required data has been loaded/replicated and is ready for initialization");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataInitialized, "InitState.DataInitialized", "3: The available data has been initialized for this actor/component, but it is not ready for full gameplay");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_GameplayReady, "InitState.GameplayReady", "4: The actor/component is fully ready for active gameplay");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_Death, "GameplayEvent.Death", "Event that fires on death. This event only fires on the server.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_Reset, "GameplayEvent.Reset", "Event that fires once a player reset is executed.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_RequestReset, "GameplayEvent.RequestReset", "Event to request a player's pawn to be instantly replaced with a new one at a valid spawn location.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_Damage, "SetByCaller.Damage", "SetByCaller tag used by damage gameplay effects.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_Heal, "SetByCaller.Heal", "SetByCaller tag used by healing gameplay effects.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cheat_GodMode, "Cheat.GodMode", "GodMode cheat is active on the owner.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cheat_UnlimitedHealth, "Cheat.UnlimitedHealth", "UnlimitedHealth cheat is active on the owner.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Crouching, "Status.Crouching", "Target is crouching.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_AutoRunning, "Status.AutoRunning", "Target is auto-running.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Death, "Status.Death", "Target has the death status.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Death_Dying, "Status.Death.Dying", "Target has begun the death process.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Death_Dead, "Status.Death.Dead", "Target has finished the death process.");
						  
	// These are mapped to the movement modes inside GetMovementModeTagMap()
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_Walking, "Movement.Mode.Walking", "Default Character movement tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_NavWalking, "Movement.Mode.NavWalking", "Default Character movement tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_Falling, "Movement.Mode.Falling", "Default Character movement tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_Swimming, "Movement.Mode.Swimming", "Default Character movement tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_Flying, "Movement.Mode.Flying", "Default Character movement tag");

	// When extending Lyra, you can create your own movement modes but you need to update GetCustomMovementModeTagMap()
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Movement_Mode_Custom, "Movement.Mode.Custom", "This is invalid and should be replaced with custom tags.  See LyraGameplayTags::CustomMovementModeTagMap.");

	const TMap<uint8, FGameplayTag> MovementModeTagMap =
	{
		{ MOVE_Walking, Movement_Mode_Walking },
		{ MOVE_NavWalking, Movement_Mode_NavWalking },
		{ MOVE_Falling, Movement_Mode_Falling },
		{ MOVE_Swimming, Movement_Mode_Swimming },
		{ MOVE_Flying, Movement_Mode_Flying },
		{ MOVE_Custom, Movement_Mode_Custom }
	};
	
	// Custom Movement Modes
	const TMap<uint8, FGameplayTag> CustomMovementModeTagMap =
	{
		// Fill these in with your custom modes
	};

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					//TODO Creating A log class
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
	
}

