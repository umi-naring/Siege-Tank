// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CUVETANK_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bIsPlayerWin);

private:
	class APlayer_Tank* PlayerTank;
public:
		void ActorDired(AActor* DeadActor);

		UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Score")
		int Score = 0;
		
		int GetAllTankCount();
		
		void HandleGameStart();
};
