// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "RocketGameCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AObstacle::AObstacle()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	RootComponent = TriggerBox;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	LeftTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTriggerBox"));
	LeftTriggerBox->SetBoxExtent(FVector(50.f, 1.f, 48.f));
	LeftTriggerBox->SetRelativeTransform(FTransform(FVector(0.f, 50.f, 0.f)));
	LeftTriggerBox->SetupAttachment(RootComponent);

	RightTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTriggerBox"));
	RightTriggerBox->SetBoxExtent(FVector(50.f, 1.f, 48.f));
	RightTriggerBox->SetRelativeTransform(FTransform(FVector(0.f, -50.f, 0.f)));
	RightTriggerBox->SetupAttachment(RootComponent);

	BottomTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomTriggerBox"));
	BottomTriggerBox->SetBoxExtent(FVector(50.f, 48.f, 1.f));
	BottomTriggerBox->SetRelativeTransform(FTransform(FVector(0.f, 0.f, -50.f)));
	BottomTriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	LeftTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnTrigger);
	RightTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnTrigger);
	BottomTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnTrigger);
}

void AObstacle::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARocketGameCharacter* Player = Cast<ARocketGameCharacter>(OtherActor);
	if (Player)
	{
		Player->Die();
	}
}
