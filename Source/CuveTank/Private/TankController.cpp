// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "UIMaster.h"

ATankController::ATankController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UUserWidget* ATankController::ShowWidget(TSubclassOf<UUserWidget> HUDClass)
{
	if (HUDClass)
	{
		MainHUDInstance = CreateWidget<UUserWidget>(this,HUDClass);
		if (MainHUDInstance)
		{
			MainHUDInstance->AddToViewport();
		}
	}
	return MainHUDInstance;
}

void ATankController::HideWidget(TSubclassOf<UUserWidget> HUDClass)
{
	if (MainHUDInstance)
	{
		MainHUDInstance->RemoveFromViewport();
		MainHUDInstance = nullptr;
	}
}