// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

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
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}
