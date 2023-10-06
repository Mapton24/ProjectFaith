// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCharacter.h"
#include "PFEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFAITH_API APFEnemy : public APFCharacter
{
	GENERATED_BODY()

public:

	APFEnemy();
	virtual void BeginPlay() override;
	
	
};
