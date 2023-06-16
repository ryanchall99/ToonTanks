// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Setting tank to the player pawn (Tank Pawn)
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); // Setting the ToonTanksPlayerController
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank) // If the actor is the tank...
    {
        if (ToonTanksPlayerController) // If true...
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false); // Set the enabled state to false
        }

        Tank->HandleDestruction(); // Handle the tanks destruction.
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) // Else if the destroyed actor can be seccessfully cast to ATower class...
    {
        DestroyedTower->HandleDestruction(); // Destroy the tower.
    }
}