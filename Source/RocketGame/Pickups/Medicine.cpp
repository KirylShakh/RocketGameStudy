// Fill out your copyright notice in the Description page of Project Settings.


#include "Medicine.h"
#include "../RocketGameCharacter.h"

void AMedicine::ProcessPickup(ARocketGameCharacter* Player)
{
    Player->Health += HealthAmount;
}