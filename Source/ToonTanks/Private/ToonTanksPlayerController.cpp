// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled) // If true...
    {
        GetPawn()->EnableInput(this); // Enables input on attached pawn
    }
    else
    {
        GetPawn()->DisableInput(this); // Disables input on attached pawn
    }

    bShowMouseCursor = bPlayerEnabled; // Enables & Disables mouse visibility based on boolean passed into function
}