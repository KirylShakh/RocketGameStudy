// Copyright Epic Games, Inc. All Rights Reserved.

#include "RocketGameGameMode.h"
#include "RocketGameCharacter.h"
#include "Tile.h"
#include "Obstacle.h"
#include "Pickups/Medicine.h"
#include "Pickups/Rocket.h"

#include "UObject/ConstructorHelpers.h"

void ARocketGameGameMode::CreateInitialTiles()
{
	for (int i = 0; i < NumInitialTiles; i++)
	{
		AddTile();
	}
}

void ARocketGameGameMode::AddTile()
{
	ATile* Tile = GetWorld()->SpawnActor<ATile>(TileClass, NextSpawnPoint);
	if (Tile)
	{
		PlacePlacebles(Tile);

		NextSpawnPoint = FTransform(FVector(0.f, NextSpawnPoint.GetTranslation().Y - TileWidth, 0.f));
		Tile->TileToDestroyAfterTrigger = LastAddedTile;
		LastAddedTile = Tile;
	}
}

void ARocketGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialTiles();
}

void ARocketGameGameMode::PlacePlacebles(ATile* Tile)
{
	TArray<TArray<FVector>> PotentialSpawnPoints = FindPotentialSpawnPoints();

	int32 NumObstacles = FMath::FloorToInt(FMath::FRandRange(0.f, MaxObstaclesPerTile));
	for (int32 i = 0; i < NumObstacles; i++)
	{
		int32 Row = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints.Num() - .6f));
		int32 Column = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints[Row].Num() - .6f));
		Tile->AddPlaceble(CreateObstacle(PotentialSpawnPoints[Row][Column]));
		
		PotentialSpawnPoints[Row].RemoveAt(Column);
		if (PotentialSpawnPoints[Row].Num() == 0)
		{
			PotentialSpawnPoints.RemoveAt(Row);
		}
	}

	int32 NumRockets = FMath::FloorToInt(FMath::FRandRange(0.f, MaxRocketsPerTile));
	for (int32 i = 0; i < NumRockets; i++)
	{
		int32 Row = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints.Num() - .6f));
		int32 Column = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints[Row].Num() - .6f));
		Tile->AddPlaceble(CreateRocket(PotentialSpawnPoints[Row][Column]));

		PotentialSpawnPoints[Row].RemoveAt(Column);
		if (PotentialSpawnPoints[Row].Num() == 0)
		{
			PotentialSpawnPoints.RemoveAt(Row);
		}
	}

	int32 NumMedicine = FMath::FloorToInt(FMath::FRandRange(0.f, MaxMedicinePerTile));
	for (int32 i = 0; i < NumMedicine; i++)
	{
		int32 Row = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints.Num() - .6f));
		int32 Column = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints[Row].Num() - .6f));
		Tile->AddPlaceble(CreateMedicine(PotentialSpawnPoints[Row][Column]));

		PotentialSpawnPoints[Row].RemoveAt(Column);
		if (PotentialSpawnPoints[Row].Num() == 0)
		{
			PotentialSpawnPoints.RemoveAt(Row);
		}
	}
}

ARocket* ARocketGameGameMode::CreateRocket(FVector Location)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform SpawnTransform = FTransform(Location);
	return GetWorld()->SpawnActor<ARocket>(RocketClass, SpawnTransform, SpawnParameters);
}

AMedicine* ARocketGameGameMode::CreateMedicine(FVector Location)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform SpawnTransform = FTransform(Location);
	return GetWorld()->SpawnActor<AMedicine>(MedicineClass, SpawnTransform, SpawnParameters);
}

AObstacle* ARocketGameGameMode::CreateObstacle(FVector Location)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform SpawnTransform = FTransform(Location);
	return GetWorld()->SpawnActor<AObstacle>(ObstacleClass, SpawnTransform, SpawnParameters);
}

TArray<TArray<FVector>> ARocketGameGameMode::FindPotentialSpawnPoints()
{
	float Y0 = NextSpawnPoint.GetTranslation().Y + TileWidth / 2.f;
	float MinY = Y0 - TileWidth;
	float Z = DownBorder;
	float MaxZ = UpBorder;

	TArray<TArray<FVector>> PotentialSpawnPoints;
	while (Z <= MaxZ)
	{
		float Y = Y0;
		TArray<FVector> Row;
		while (Y > MinY)
		{
			Row.Add(FVector(0.f, Y, Z));
			Y -= PlacebleSide;
		}
		PotentialSpawnPoints.Add(Row);
		Z += PlacebleSide;
	}
	return PotentialSpawnPoints;
}
