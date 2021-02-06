// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class ROCKETGAME_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* TriggerBox;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
