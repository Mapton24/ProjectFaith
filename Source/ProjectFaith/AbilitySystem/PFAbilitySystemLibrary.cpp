// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAbilitySystemLibrary.h"

#include "ProjectFaith/Player/PFPlayerState.h"
#include "ProjectFaith/UI/HUD/PFHUD.h"
#include "ProjectFaith/UI/WidgetController/PFWidgetController.h"
#include "Kismet/GameplayStatics.h"


UOverlayWidgetController* UPFAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		if (APFHUD* PFHUD = Cast<APFHUD>(PC->GetHUD()))
		{
			APFPlayerState* PS = PC->GetPlayerState<APFPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return PFHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UPFAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		if (APFHUD* PFHUD = Cast<APFHUD>(PC->GetHUD()))
		{
			APFPlayerState* PS = PC->GetPlayerState<APFPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return PFHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
