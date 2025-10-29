// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBase.h"
#include "Enemy_Tank.generated.h"

/**
 * 
 */
UCLASS()
class CUVETANK_API AEnemy_Tank : public ATankBase
{
	GENERATED_BODY()


	private:

	UPROPERTY(EditAnywhere, Category = "AI")
	float StopDistance = 2000.f; // 플레이어와 유지할 최소 거리
	UPROPERTY(EditAnywhere, Category = "AI")
	float error = 100.f;

	private:
		APawn* PlayerPawn;

		FVector MoveDirection = FVector::ZeroVector;

		void Move(float DeltaTime);
		void AIFire();

		bool bCanAttack = true;

		APlayerController* PlayerController = nullptr;

		

	protected:

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

	public:
		AEnemy_Tank();	

		UFUNCTION()
		void LookAtTarget(FVector TargetPoint, float RotSpeed);

		FVector MyLocation;
		FVector PlayerLocation;

};
