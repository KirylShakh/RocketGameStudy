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

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* LeftTriggerBox;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* RightTriggerBox;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BottomTriggerBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
