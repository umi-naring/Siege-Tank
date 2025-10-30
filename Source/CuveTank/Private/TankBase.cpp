// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBase.h"
#include "Explosion.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ATankBase::ATankBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HP"));

	TurretSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Scene"));
	TurretSceneRoot ->SetupAttachment(GetMesh());

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BombScene"));
	SceneRoot->SetupAttachment(TurretSceneRoot);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(100.f, 0.f, 50.f));
}

// Called when the game starts or when spawned
void ATankBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankBase::Fire()
{
	FTransform SpawnBulletTransform = ProjectileSpawnPoint->GetComponentTransform();
	SpawnBullet(SpawnBulletTransform);
}

AProjectile* ATankBase::SpawnBullet(FTransform transform)
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, transform);

	if (Projectile != nullptr)
	{
		Projectile->SetOwner(this);
	}

	return Projectile;
}


//float AABasePawn::TakeDamage(
//	float DamageAmount,
//	FDamageEvent const& DamageEvent,
//	AController* EventInstigator,
//	AActor* DamageCauser)
//{
//	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//	HealthComp->Health -= ActualDamage;
//	ATankGameMode* GameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(this));
//
//	if (HealthComp->Health <= 0)
//	{
//		// 폭발 이펙트 생성
//		// 본인 파괴
//		Destroy();
//
//		GameMode->ActorDired(DamagedActor);
//	}
//	return ActualDamage;
//}
void ATankBase::HandleDestruction()
{

}

