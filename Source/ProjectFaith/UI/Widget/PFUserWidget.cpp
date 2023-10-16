// Fill out your copyright notice in the Description page of Project Settings.


#include "PFUserWidget.h"

void UPFUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
