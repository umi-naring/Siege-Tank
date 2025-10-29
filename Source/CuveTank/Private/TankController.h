// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class ATankController : public APlayerController
{
	GENERATED_BODY()

private:
	UUserWidget* MainHUDInstance;

public:
	ATankController();

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* ShowWidget(TSubclassOf<UUserWidget> HUDClass);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideWidget(TSubclassOf<UUserWidget> HUDClass);

protected:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;	

};
