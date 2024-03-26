// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PFPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;


/** This defines the player type, if it's either active or not */
UENUM()
enum class EPFPlayerConnectionType : uint8
{
	Player = 0,

	InactivePlayer
};
/**
 * Base player state class for this project.
 */
UCLASS()
class PROJECTFAITH_API APFPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APFPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PF|PlayerState")
	UPFAbilitySystemComponent* GetPFAbilitySystemComponent() const { return AbilitySystemComponent; }
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//Actor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	//End of AActor interface

	//APlayerState interface
	virtual void Reset() override;
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OnDeactivated() override;
	virtual void OnReactivated() override;

	FORCEINLINE int32 GetPlayerLevel() const {return Level; }

	void SetPlayerConnectionType(EPFPlayerConnectionType NewType);
	EPFPlayerConnectionType GetPlayerConnectionType() const { return MyPlayerConnectionType; }

private:
	UPROPERTY(VisibleAnywhere, Category = "PF|PlayerState")
	TObjectPtr<UPFAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;
	UPROPERTY(Replicated)
	EPFPlayerConnectionType MyPlayerConnectionType;
};

