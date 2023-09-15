// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "ProjectFaith/AbilitySystem/PFAbilitySystemComponent.h"
#include "Engine/World.h"

class AController;
class APlayerState;
class FLifetimeProperty;

APFPlayerState::APFPlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UPFAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void APFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyPlayerConnectionType, SharedParams);
	
}

UAbilitySystemComponent* APFPlayerState::GetAbilitySystemComponent() const
{
	return GetPFAbilitySystemComponent();
}

void APFPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void APFPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}

void APFPlayerState::Reset()
{
	Super::Reset();
}

void APFPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
}

void APFPlayerState::OnDeactivated()
{
	bool bDestroyDeactivatedPlayerState = false;

	switch(GetPlayerConnectionType())
	{
	case EPFPlayerConnectionType::Player:
	case EPFPlayerConnectionType::InactivePlayer:
		bDestroyDeactivatedPlayerState = true;
		break;
	default:
		bDestroyDeactivatedPlayerState = true;
		break;
	}
	
	SetPlayerConnectionType(EPFPlayerConnectionType::InactivePlayer);

	if (bDestroyDeactivatedPlayerState)
	{
		Destroy();
	}
}

void APFPlayerState::OnReactivated()
{
	if (GetPlayerConnectionType() == EPFPlayerConnectionType::InactivePlayer)
	{
		SetPlayerConnectionType(EPFPlayerConnectionType::Player);
	}
}


void APFPlayerState::SetPlayerConnectionType(EPFPlayerConnectionType NewType)
{
	//TODO fix this macro, compiler might fail
	//MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, MyPlayerConnectionType, this);
	MyPlayerConnectionType = NewType;
}

