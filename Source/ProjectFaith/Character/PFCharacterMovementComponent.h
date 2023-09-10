// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"

#include "PFCharacterMovementComponent.generated.h"

class UObject;
struct FFrame;


/**
 * 
 */
USTRUCT(BlueprintType)
struct FPFCharacterGroundInfo
{
	GENERATED_BODY()

	FPFCharacterGroundInfo()
		: LastUpdateFrame(0)
	    , GroundDistance(0.0f)
	{}

	uint64 LastUpdateFrame;

	UPROPERTY(BluePrintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

UCLASS(Config = Game)
class PROJECTFAITH_API UPFCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UPFCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void SimulateMovement(float DeltaTime) override;

	virtual bool CanAttemptJump() const override;

	//Returns current ground info. Calling it updates the ground info
	UFUNCTION(BlueprintCallable, Category = "PF|CharacterMovement")
	const FPFCharacterGroundInfo& GetGroundInfo();

protected:
	
	virtual void InitializeComponent() override;

protected:
	
	FPFCharacterGroundInfo CachedGroundInfo;
	
};
