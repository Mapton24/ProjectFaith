// Fill out your copyright notice in the Description page of Project Settings.


#include "PFWidgetController.h"

void UPFWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
	
}

void UPFWidgetController::BroadcastInitialValues()
{
	
}

void UPFWidgetController::BindCallbacksToDependencies()
{
	
}
