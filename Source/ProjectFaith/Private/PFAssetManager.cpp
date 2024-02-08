// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAssetManager.h"
#include "ProjectFaith/PFGameplayTags.h"

UPFAssetManager& UPFAssetManager::Get()
{
	check(GEngine);
	
	UPFAssetManager* PFAssetManager = Cast<UPFAssetManager>(GEngine->AssetManager);
	return *PFAssetManager;
}

void UPFAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FPFGameplayTags::InitializeNativeGameplayTags();
}
