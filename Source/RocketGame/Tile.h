// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class ROCKETGAME_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Wrapper;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* TriggerBox;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float DeathDelay = 5.f;

	ATile* TileToDestroyAfterTrigger;

	void AddPlaceble(AActor* Placeble);

	void DestroySelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	class ARocketGameGameMode* RocketGameGameMode;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	void OnDestroyTimerCompleted();

	TArray<AActor*> Placebles;

	void OnPlacebleDestroyed(AActor* DestroyedActor);
};
