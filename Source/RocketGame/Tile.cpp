// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "RocketGameGameMode.h"
#include "RocketGameCharacter.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATile::ATile()
{
	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(64.f, 64.f, 1000.f));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ATile::AddPlaceble(AActor* Placeble)
{
	Placebles.Add(Placeble);
	Placeble->OnDestroyed.AddDynamic(this, &ATile::OnPlacebleDestroyed);
}

void ATile::DestroySelf()
{	
	for (int i = 0; i < Placebles.Num(); i++)
	{
		if (Placebles[i])
		{
			Placebles[i]->Destroy();
		}
	}
	Placebles.Empty();

	Destroy();
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	RocketGameGameMode = Cast<ARocketGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(RocketGameGameMode);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnTrigger);
}

void ATile::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocketGameCharacter>(OtherActor))
	{
		RocketGameGameMode->AddTile();

		if (TileToDestroyAfterTrigger)
		{
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ATile::OnDestroyTimerCompleted, DeathDelay, false);
		}
		TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ATile::OnTrigger);
	}
}

void ATile::OnDestroyTimerCompleted()
{
	if (DestroyTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}

	TileToDestroyAfterTrigger->DestroySelf();
	TileToDestroyAfterTrigger = nullptr;
}

void ATile::OnPlacebleDestroyed(AActor* DestroyedActor)
{
	if (Placebles.Find(DestroyedActor) != -1)
	{
		Placebles.Remove(DestroyedActor);
	}
}

