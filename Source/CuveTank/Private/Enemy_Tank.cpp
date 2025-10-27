// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Tank.h"
#include "Kismet/GameplayStatics.h"

AEnemy_Tank::AEnemy_Tank()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void AEnemy_Tank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 월드에서 첫 번째 플레이어 Pawn 가져오기
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
	
void AEnemy_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = PlayerPawn->GetActorLocation();
	MyLocation = GetActorLocation();

	if (PlayerController)
	{
		PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		LookAtTarget(PlayerLocation, 1);
	}
	Move(MoveSpeed * DeltaTime);
}
	
void AEnemy_Tank::LookAtTarget(FVector TargetPoint, float RotSpeed)
{
	FVector ToTarget = TargetPoint - GetMesh()->GetComponentLocation();

	FRotator TargetRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		
	FQuat NewRotation = FQuat::Slerp(GetMesh()->GetRelativeRotation().Quaternion(),
		TargetRotation.Quaternion(), RotSpeed);

	GetMesh()->SetWorldRotation(NewRotation);
	
	ToTarget.Normalize();
	MoveDirection = ToTarget;	
}

void AEnemy_Tank::Move(float Value)
{
	if (!PlayerController || !PlayerController->GetPawn()) return;

	FTimerHandle FAttackHandle;

	PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
	MyLocation = GetActorLocation();

	FVector ToPlayer = PlayerLocation - MyLocation;
	float Distance = ToPlayer.Size();
	if (Distance <= KINDA_SMALL_NUMBER) return;

	FVector Direction = ToPlayer.GetSafeNormal();

	float MinRange = StopDistance - error;
	float MaxRange = StopDistance + error;

	if (Distance > MaxRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Over MaxRange."));
		AddMovementInput(Direction, Value);
	}
	else if (Distance < MinRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Under MinRange."));
		AddMovementInput(-Direction, Value);
	}
	else if(bCanAttack)
	{
		SpawnBullet(ProjectileSpawnPoint->GetComponentTransform());

		bCanAttack = false;

		GetWorld()->GetTimerManager().SetTimer(
			FAttackHandle,
			this, 
			&AEnemy_Tank::AIFire, 
			AttackSpeed, 
			false);
	}
}
void AEnemy_Tank::AIFire()
{
	bCanAttack = true;
}