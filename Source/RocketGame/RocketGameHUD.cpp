// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketGameHUD.h"
#include "RocketGameCharacter.h"

#include "Kismet/GameplayStatics.h"

void ARocketGameHUD::DrawHUD()
{
    Super::DrawHUD();

    ARocketGameCharacter* Player = Cast<ARocketGameCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!Player)
    {
        return;
    }

    TArray<FString> Messages;
    Messages.Add("Rockets remaining: " + FString::FromInt(Player->Rockets));
    Messages.Add("Health remaining: " + FString::FromInt(Player->Health));

    for (int i = Messages.Num() - 1; i >= 0; i--)
    {
        float outputWidth, outputHeight;
        GetTextSize(Messages[i], outputWidth, outputHeight, HudFont, 1.f);
        float messageH = outputHeight + 2.f * PadY;
        float x = 0.f, y = i * messageH;

        DrawText(Messages[i], TextColor, x + PadX, y + PadY, HudFont, TextScale);
    }

    Messages.Empty();
}
