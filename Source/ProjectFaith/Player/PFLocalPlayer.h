 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Engine/LocalPlayer.h"

#include "PFLocalPlayer.generated.h"

struct FGenericTeamId;

class APlayerController;


/**
 * PFLocalPlayer
 */
UCLASS()
class PROJECTFAITH_API UPFLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	UPFLocalPlayer();

	//~UObject interface
	virtual void PostInitProperties() override;

	//~UPlayer interface
	
	// UFUNCTION()
	// UPFSettingsLocal* GetLocalSettings() const;

private:

	UPROPERTY(Transient)
	mutable TObjectPtr<const UInputMappingContext> InputMappingContext;
};
