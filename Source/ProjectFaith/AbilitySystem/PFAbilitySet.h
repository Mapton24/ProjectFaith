// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayAbilitySet.h"

#include "AttributeSet.h"
#include "PFAbilitySet.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UPFAbilitySystemComponent;
class UPFGameplayAbility;
class UObject;
/**
 *  Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FPFAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:
	
	//Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPFGameplayAbility> Ability = nullptr;

	//Level of ability to grand.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * FPFAbilitySet_GameplayEffect
 *
 * Data used by ability set to grand gameplay effects
 */

USTRUCT(BlueprintType)
struct FPFAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	//Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	//Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * FPFAbilitySet_AttributeSet
 *
 * Data used by ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FPFAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:

	//Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};

/**
 * Data used to store handles to what has been granted by ability set.
 *
 */
USTRUCT(BlueprintType)
struct FPFAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UPFAbilitySystemComponent* PFASC);

protected:

	//Handles to granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	//Handles to granted gameplay effects;
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	//Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

UCLASS(BlueprintType, Const)
class PROJECTFAITH_API UPFAbilitySet : public UGameplayAbilitySet
{
	GENERATED_BODY()

public:
	UPFAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//Grants the ability set to the specified ability system component.
	// The returned handles can be used later to take away anything that was granted.
	void GiveToAbilitySystem(UPFAbilitySystemComponent* PFASC, FPFAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FPFAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FPFAbilitySet_GameplayEffect> GrantedGameplayEffects;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta=(TitleProperty=AttributeSet))
	TArray<FPFAbilitySet_AttributeSet> GrantedAttributes;
	
};
