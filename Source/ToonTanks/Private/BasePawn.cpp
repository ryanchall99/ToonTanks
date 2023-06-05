// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collider"); // Creates a Capsule Component Called "Capsule Collider"
	RootComponent = CapsuleComp; // Sets the Capsule Component As the Root Component

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh"); // Creates Static Mesh Component Named "Base Mesh"
	BaseMesh->SetupAttachment(CapsuleComp); // Attaches the base mesh to the Capsule Component (Root Component)

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh"); // Creates Static Mesh Component Named "Turret Mesh"
	TurretMesh->SetupAttachment(BaseMesh); // Attaches the turret mesh to the base mesh

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point"); // Creates Scene Component Named "Projectile Spawn Point"
	ProjectileSpawnPoint->SetupAttachment(TurretMesh); // Attaches the Projectile Spawn Point to turret mesh
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

