// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PFInputConfig.h"

#include "PFInputComponent.generated.h"


class UEnhancedInputLocalPlayerSubsystem;
/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UPFInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UPFInputComponent(const FObjectInitializer& ObjectInitializer);

	void AddInputMappings(const UPFInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const UPFInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;


	
	
};
