// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent) // Implemented In BluePrints
		void StartGame(); // Function For When Game Starts


private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController; // Custom Controller For Player

	void HandleGameStart();
	float StartDelay = 4.f;


};
