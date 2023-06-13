// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    // SPRING ARM SETUP
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);

    // CAMERA SETUP
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

    // Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            SubSystem->AddMappingContext(MappingContext, 0);
        }
    }
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController) // If PlayerControllerRef not null...
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult); // Get the hit result of the cursor

        RotateTurret(HitResult.ImpactPoint); // Rotate the turret based on the hit results impact point.
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true); // Hides the tank (Maintains Camera)
    SetActorTickEnabled(false); // Stops the tanks ticking
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::MoveForward);
        EnhancedInputComponent->BindAction(InputRotate, ETriggerEvent::Triggered, this, &ATank::Rotate);
        EnhancedInputComponent->BindAction(InputFire, ETriggerEvent::Started, this, &ATank::Fire);
    }

}

void ATank::MoveForward(const FInputActionValue& Value)
{
    float MoveValue = Value.Get<float>(); // Getting float value (1 / -1)
    FVector DeltaLocation = FVector::ZeroVector;

    DeltaLocation.X += MoveValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); // Movement in X direction (Backwards / Forwards)
    AddActorLocalOffset(DeltaLocation, true); // Setting the local offset of actor based on this new FVector
}

void ATank::Rotate(const FInputActionValue& Value)
{
    float RotateValue = Value.Get<float>(); // Getting float value (1 / -1)
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw += RotateValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this); // Movement in YAW
    AddActorLocalRotation(DeltaRotation, true); // Setting the local rotation of actor based on this new FRotator
}