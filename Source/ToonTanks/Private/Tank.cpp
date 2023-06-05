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
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

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

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::MoveForward);
        EnhancedInputComponent->BindAction(InputRotate, ETriggerEvent::Triggered, this, &ATank::Rotate);
    }

}

void ATank::MoveForward(const FInputActionValue& Value)
{
    float MoveValue = Value.Get<float>();
    FVector DeltaLocation = FVector::ZeroVector;

    DeltaLocation.X += MoveValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Rotate(const FInputActionValue& Value)
{
    float RotateValue = Value.Get<float>();
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw += RotateValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}