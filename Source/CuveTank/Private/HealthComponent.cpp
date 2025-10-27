// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Explosion.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameMode.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	// 언리얼 기본 대미지 전달 가능
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageToken);


	// ...
	
}
AExplosion* UHealthComponent::Explosion_Enemy(AActor* DamagedActor, FTransform transform)
{
	AExplosion* Explosion = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, transform);

	if (Explosion != nullptr)
	{
		Explosion->SetOwner(DamagedActor);
	}

	return Explosion;

}
void UHealthComponent::DamageToken(AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	ATankGameMode* GameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(this));
	
	Health -= Damage;
	if (Health <= 0.f)
	{
		Explosion_Enemy(DamagedActor,DamagedActor->GetActorTransform());
		GameMode->ActorDired(DamagedActor);
	}
}

void UHealthComponent::GetHealth(float& _currentHealth, float& _Maxhealth)
{
	_currentHealth = this->Health;
	_Maxhealth = this->MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

