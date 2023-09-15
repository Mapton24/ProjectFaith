// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAbilitySet.h"

#include "PFAbilitySystemComponent.h"
#include "ProjectFaith/AbilitySystem/Abilities/PFGameplayAbility.h"

void FPFAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FPFAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FPFAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set)
{
	GrantedAttributeSets.Add(Set);
}

void FPFAbilitySet_GrantedHandles::TakeFromAbilitySystem(UPFAbilitySystemComponent* PFASC)
{
	check(PFASC);

	if (!PFASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			PFASC->ClearAbility(Handle);
		}
	}
	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			PFASC->RemoveActiveGameplayEffect(Handle);
		}
	}
	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			PFASC->ClearAbility(Handle);
		}
	}
}

UPFAbilitySet::UPFAbilitySet(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPFAbilitySet::GiveToAbilitySystem(UPFAbilitySystemComponent* PFASC,
	FPFAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	check(PFASC);

	if(!PFASC->IsOwnerActorAuthoritative())
	{
		//Must be authoritative to give or take ability sets
		return;
	}
	//Grand the gameplay abilities.
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FPFAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			//TODO Create log channels.
			//UE_LOG(Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}
		UPFGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UPFGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = PFASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	//Grant the gameplay effects.
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
	{
		const FPFAbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[EffectIndex];

		if (!IsValid(EffectToGrant.GameplayEffect))
		{
			//TODO Create log channels.
			continue;
		}
		const UGameplayEffect* GameplayEffect = EffectToGrant.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle GameplayEffectHandle = PFASC->ApplyGameplayEffectToSelf(GameplayEffect, EffectToGrant.EffectLevel, PFASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const FPFAbilitySet_AttributeSet& SetToGrant = GrantedAttributes[SetIndex];

		if (!IsValid(SetToGrant.AttributeSet))
		{
			//TODO Create log channels.
			continue;
		}
		UAttributeSet* NewSet = NewObject<UAttributeSet>(PFASC->GetOwner(), SetToGrant.AttributeSet);
		PFASC->AddAttributeSetSubobject(NewSet);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAttributeSet(NewSet);
		}
	}
	
}
