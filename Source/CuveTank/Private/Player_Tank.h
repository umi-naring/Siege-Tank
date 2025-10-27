// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBase.h"
#include "Player_Tank.generated.h"

/**
 *
 */
UCLASS()
class CUVETANK_API APlayer_Tank : public ATankBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	FVector MoveDirection = FVector::ZeroVector;


private :
	APlayerController* TankPlayerController = nullptr;

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	APlayer_Tank();

	void Move(float DeltaTime);
	void UDMove(float Value);
	void TurretMove(float Value);
	void TurretTurn(float Value);

	void MousePointerRotation(float delta);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BaseEnableInput(bool bEnable);
};
