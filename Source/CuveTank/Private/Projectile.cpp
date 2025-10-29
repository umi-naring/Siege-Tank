// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

//파티클 시스템
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Projectilemesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = Projectilemesh;

	ProjectileMovementComponent
		= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Projectilemesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);//&OnHit 함수 포인터, 델리게이트

	UGameplayStatics::SpawnEmitterAtLocation(
		this,
		StartParticles, 
		GetActorLocation(),
		GetActorRotation(),
		FVector(2.f,2.f,2.f)
	);

	UGameplayStatics::SpawnEmitterAtLocation(
		this,
		StartEXPParticles,
		GetActorLocation(),
		GetActorRotation(),
		FVector(1.f, 1.f, 1.f)
	);
}
void AProjectile::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{ 
	//총알 생성한 객체(오너, 주인)의 주소

	//총알 생성한 객체인 주인의 탱크 베이스 끌고 와서 함수 선언을 해주고 싶음
	ATankBase* MyOwner = Cast<ATankBase>(GetOwner());

	if(MyOwner == nullptr)
	{
		Destroy();	
		return;
	}

	//충돌한 객체가 내 주인이 아닐때만

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	//대미지 속성을 넣으려면 UDamageType을 상속받은 클래스를 만들어서 넣어주면 된다.
	// 
	//내 주인이 아니고, 나 자신도 아니고, 널포인터도 아닐때
	if (OtherActor != MyOwner && OtherActor != this && OtherActor != nullptr)
	{
		ATankBase* Enemy = Cast<ATankBase>(OtherActor);// Enemy_Tank(ABasePawn 상속)인지 확인


		if (Enemy)
		{
			// 데미지 적용
			UGameplayStatics::ApplyDamage(
				Enemy,          // 대상
				DamageCalculate(MyOwner->SendAttack, Enemy->SendDefense),         // float DamageAmount (Projectile에 변수로 만들어둬)
				GetInstigatorController(), // 누가 발사했는지
				this,           // DamageCauser
				UDamageType::StaticClass() // 데미지 타입
			);
		}
		if(HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation()
			);
		if(HitSound)
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation()
			);
	}
	Destroy();
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

float AProjectile::DamageCalculate(float OwnerAttack, float EnemyDefense)
{
	float EndDamage = OwnerAttack * Damage;

	if (EndDamage <= 0.f)
	{
		EndDamage = 1.f;
	}

	return EndDamage;
}
