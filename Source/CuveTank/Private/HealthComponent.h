// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUVETANK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystemComponent* DeathParticle;
public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditAnywhere, Category = "HP")
	float MaxHealth = 5000.f;
	UPROPERTY(EditAnywhere, Category = "HP")
	float Health = 0.f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void DamageToken(AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void GetHealth(float& _currentHealth, float& _Maxhealth);

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AExplosion> ExplosionClass;

	class AExplosion* Explosion_Enemy(AActor* DamagedActor, FTransform transform);
};
