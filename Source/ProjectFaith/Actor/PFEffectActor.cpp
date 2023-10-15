// Fill out your copyright notice in the Description page of Project Settings.


#include "PFEffectActor.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "ProjectFaith/Attributes/PFAttributeSet.h"

// Sets default values
APFEffectActor::APFEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void APFEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UPFAttributeSet* PFAttributeSet = Cast<UPFAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UPFAttributeSet::StaticClass()));
		
		UPFAttributeSet* MutablePFAttributeSet = const_cast<UPFAttributeSet*>(PFAttributeSet);
		MutablePFAttributeSet->SetHealth(PFAttributeSet->GetHealth() + 20.f);
		Destroy();
	}
}

void APFEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void APFEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APFEffectActor::OnOverlap);
	//Sphere->OnComponentEndOverlap.AddDynamic(this, &APFEffectActor::EndOverlap);
	
}


