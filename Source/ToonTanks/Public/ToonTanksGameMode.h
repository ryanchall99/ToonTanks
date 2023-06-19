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

	UFUNCTION(BlueprintImplementableEvent) // Implemented In BluePrints
		void GameOver(bool bWonGame); // Function For When Game Ends (false = loss, true = win)


private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController; // Custom Controller For Player

	void HandleGameStart();
	float StartDelay = 4.f;

	int32 TargetTowers = 0; // Amount of towers in game
	int32 GetTargetTowerCount(); // Getter for amount of towers

};
