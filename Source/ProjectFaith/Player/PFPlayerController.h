// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PFPlayerController.generated.h"

struct FGenericTeamId;

class APawn;
class UPFAbilitySystemComponent;
class UObject;
class UPlayer;
struct FFrame;

/**
 * 
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class PROJECTFAITH_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APFPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//UFUNCTION(BlueprintCallable, Category = "PF|PlayerController")
	//UPFAbilitySystemComponent* GetPFAbilitySystemComponent() const;
	
	
};
