// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHUD.h"

#include "Blueprint/UserWidget.h"

#include "ProjectFaith/UI/Widget/PFUserWidget.h"
#include "ProjectFaith/UI/WidgetController/AttributeMenuWidgetController.h"
#include "ProjectFaith/UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* APFHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* APFHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();

		return AttributeMenuWidgetController;
	}
	return AttributeMenuWidgetController;
}

void APFHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please fill out BP_PFHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_PFHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UPFUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
	
	
}


