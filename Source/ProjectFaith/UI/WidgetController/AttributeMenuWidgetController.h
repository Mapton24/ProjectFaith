// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTFAITH_API UAttributeMenuWidgetController : public UPFWidgetController
{
	GENERATED_BODY()

public:

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;


private:
};
