// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "HealthComponent.h"
#include "TankBase.h"
#include "Player_Tank.h"
#include "Kismet/GameplayStatics.h"	

ATankGameMode::ATankGameMode()
{
	//게임 시작 UI 처리

}
void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStart();

	PlayerTank = Cast<APlayer_Tank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerTank->BaseEnableInput(false);

	FTimerHandle PlayerEnableTimerHandle;

	FTimerDelegate PlayerEnableDelegate =
	FTimerDelegate::CreateUObject(this, &ATankGameMode::HandleGameStart);

	GetWorldTimerManager().SetTimer(
		PlayerEnableTimerHandle,
		PlayerEnableDelegate,
		0.01f,
		false
	);
}
void ATankGameMode::ActorDired(AActor* DeadActor)
{
	if(PlayerTank == DeadActor)
	{
		PlayerTank->HandleDestruction();
		//플레이어 죽음
		//게임 오버 처리
			GameOver(false);
			//게임 승리
			//게임 오버 처리
			PlayerTank->BaseEnableInput(false);
	}
	else
	{
		//적 탱크 죽음
		int count = GetAllTankCount();
		if(count <= 2)
		{
			GameOver(true);
			//게임 승리
			//게임 오버 처리
		}
		Score += 100;
	}
	ATankBase*DestroyActor = Cast<ATankBase>(DeadActor);
	if(DestroyActor)
	{
		DestroyActor->HandleDestruction();
	}
	DeadActor->Destroy();
}
 
int ATankGameMode::GetAllTankCount()
{
	TArray<AActor*> EnemyTank;
	UGameplayStatics::GetAllActorsOfClass(this, ATankBase::StaticClass(), EnemyTank);
	int32 Count = EnemyTank.Num();
	
	return EnemyTank.Num();
}

void ATankGameMode::HandleGameStart()
{
	if (PlayerTank)
	{
		PlayerTank->BaseEnableInput(true);
	}
}