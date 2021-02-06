// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RocketGameGameMode.generated.h"

class ATile;
class ARocket;
class AMedicine;
class AObstacle;

UCLASS(minimalapi)
class ARocketGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<ATile> TileClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint = FTransform(FVector(0.f, 0.f, 0.f));

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialTiles = 5;

	UPROPERTY(EditAnywhere, Category = "Config")
	float TileWidth = 2000.f;

	void CreateInitialTiles();

	void AddTile();

	UPROPERTY(EditAnywhere, Category = "Config")
	float DownBorder = 25.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float UpBorder = 1025.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<ARocket> RocketClass;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AMedicine> MedicineClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AObstacle> ObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	float PlacebleSide = 100.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 MaxRocketsPerTile = 15;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 MaxMedicinePerTile = 10;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 MaxObstaclesPerTile = 20;

protected:
	virtual void BeginPlay() override;

	ATile* LastAddedTile = nullptr;

	void PlacePlacebles(ATile* Tile);

	ARocket* CreateRocket(FVector Location);
	AMedicine* CreateMedicine(FVector Location);
	AObstacle* CreateObstacle(FVector Location);

	TArray<TArray<FVector>> FindPotentialSpawnPoints();
};



