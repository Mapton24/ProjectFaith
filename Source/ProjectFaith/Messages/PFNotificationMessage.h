// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "PFNotificationMessage.generated.h"

struct FGameplayTag;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPFNotificationMessage : public FTableRowBase
{
 GENERATED_BODY()

 UPROPERTY(EditAnywhere, BlueprintReadOnly)
 FGameplayTag MessageTag = FGameplayTag();
 
 UPROPERTY(EditAnywhere, BlueprintReadOnly)
 FText Message = FText();
 
 UPROPERTY(EditAnywhere, BlueprintReadOnly)
 TSubclassOf<class UPFUserWidget> MessageWidget;
 
 UPROPERTY(EditAnywhere, BlueprintReadOnly)
 UTexture2D* Image = nullptr;
};
