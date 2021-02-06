// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "../RocketGameCharacter.h"

void ARocket::ProcessPickup(ARocketGameCharacter* Player)
{
    Player->Rockets += RocketsNum;
}