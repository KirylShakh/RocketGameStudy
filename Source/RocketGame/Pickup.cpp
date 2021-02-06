// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "RocketGameCharacter.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickup::APickup()
{
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Capsule"));
	TriggerSphere->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RootComponent = TriggerSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnTrigger);
}

void APickup::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARocketGameCharacter* Player = Cast<ARocketGameCharacter>(OtherActor);
	if (Player)
	{
		ProcessPickup(Player);
		Destroy();
	}
}

void APickup::ProcessPickup(ARocketGameCharacter* Player)
{
}

