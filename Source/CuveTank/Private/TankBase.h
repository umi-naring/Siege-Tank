// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "TankBase.generated.h"

UCLASS()
class CUVETANK_API ATankBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Attack = 10.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Defense = 5.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 100.f;

public:
	float SendAttack = Attack;
	float SendDefense = Defense;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* TurretSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneRoot;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class USoundBase* DeathSound;
public:
	// Sets default values for this pawn's properties
	ATankBase();

	void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector CheckFloor();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;*/

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	class AProjectile* SpawnBullet(FTransform transform);

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

};
