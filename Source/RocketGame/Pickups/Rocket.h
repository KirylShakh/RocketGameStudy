// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickup.h"
#include "Rocket.generated.h"

class ARocketGameCharacter;

UCLASS()
class ROCKETGAME_API ARocket : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int32 RocketsNum = 1;

protected:
	virtual void ProcessPickup(ARocketGameCharacter* Player) override;
};
