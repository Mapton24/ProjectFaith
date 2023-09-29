// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacterMain.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APFCharacterMain::APFCharacterMain()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom);
	
}
