// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &ATower::CheckFireCondition,
        FireRate,
        true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Check if tank is in range
    if (InFiringRange())
    {
        // If in range, rotate turret towards tank
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::CheckFireCondition()
{
    if (InFiringRange())
    {
        Fire();
    }
}

bool ATower::InFiringRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        return Distance <= FireRange;
    }

    return false;
}