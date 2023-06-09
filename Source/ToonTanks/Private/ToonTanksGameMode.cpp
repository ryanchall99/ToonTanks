// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart(); // Handles All The Start Of Game Functionality
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

        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) // Else if the destroyed actor can be seccessfully cast to ATower class...
    {
        DestroyedTower->HandleDestruction(); // Destroy the tower.
        TargetTowers--; // Subtracts 1 from tower count

        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount(); // Setting the target towers amount
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Setting tank to the player pawn (Tank Pawn)
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); // Setting the ToonTanksPlayerController

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false); // Sets player input to false on start.

        FTimerHandle PlayerEnableTimerHandle; // Timer Handle For Enabling Input
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        ); // Timer Delegate That Runs SetPlayerEnabledState Function With True Passed In After Elapsed Time

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        ); // Setting Timer, Runs The Delegate After Delay (Does Not Loop)

    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers; // Initialising Out Parameter
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers); // Gets all actors of type ATower & Outputs them into Towers TArray

    return Towers.Num(); // Returning the Number of Tower Actors in TArray
}