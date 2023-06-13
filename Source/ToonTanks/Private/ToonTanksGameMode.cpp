// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Setting tank to the player pawn (Tank Pawn)
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank) // If the actor is the tank...
    {
        if (Tank->GetTankPlayerController())
        {
            Tank->DisableInput(Tank->GetTankPlayerController()); // Disable any inputs into the player controller.
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }

        Tank->HandleDestruction(); // Handle the tanks destruction.
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) // Else if the destroyed actor can be seccessfully cast to ATower class...
    {
        DestroyedTower->HandleDestruction(); // Destroy the tower.
    }
}