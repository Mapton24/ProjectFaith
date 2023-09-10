// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"

#include "PFCharacter.generated.h"


class AActor;
class AController;
class APFPlayerController;
class UInputComponent;
class UPFAbilitySystemComponent;
class UAbilitySystemComponent;
class UObject;
struct FFrame;
struct FGameplayTag;
struct FGameplayTagContainer;



UCLASS(Config = Game, Meta = (ShortTooltip = "Base character pawn class"))
class PROJECTFAITH_API APFCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APFCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "PF|Character")
	APFPlayerController* GetPFPlayerController() const;

	UFUNCTION(Blueprintable, Category = "PF|Character")
	UPFAbilitySystemComponent* GetPFAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	//Interface of GameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PF|Character", Meta = (AllowPrivateAccess = "true"))


};
