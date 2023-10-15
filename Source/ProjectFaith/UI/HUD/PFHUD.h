// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PFHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UPFUserWidget;
/**
 * 
 */
UCLASS()
class PROJECTFAITH_API APFHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	
public:
	UPROPERTY()
	TObjectPtr<UPFUserWidget> OverlayWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPFUserWidget> OverlayWidgetClass;
	
};
