// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PFAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API UPFAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UPFAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
