// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h" // 디버그용 라인트레이스 시각화

APlayer_Tank::APlayer_Tank()
{
    PrimaryActorTick.bCanEverTick = true;


    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 10000.f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.f;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void APlayer_Tank::BeginPlay()
{
    Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
}

void APlayer_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("UpAndDown"), this, &APlayer_Tank::UDMove);
	PlayerInputComponent->BindAxis(TEXT("TurretUp"), this, &APlayer_Tank::TurretMove);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATankBase::Fire);
}

void APlayer_Tank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	MousePointerRotation(DeltaTime);

	/*Move(DeltaTime);*/
}

//void APlayer_Tank::Move(float DeltaTime)
//{
//    // 이동 처리
//    if (MoveDirection.IsNearlyZero()) return;
//
//    FVector Forward = GetActorForwardVector();
//    FVector Right = GetActorRightVector();
//    FVector InputDirection = (Forward * MoveDirection.X) + (Right * MoveDirection.Y);
//    InputDirection.Normalize();
//    
//	FVector SurfaceNormal = CheckFloor();
//
//    if (SurfaceNormal.Size() != 0)
//    {
//        FVector ProjectedDirection = InputDirection + FVector(0, 0, SurfaceNormal.Z);
//
//        ProjectedDirection.Normalize();
//
//        AddMovementInput(ProjectedDirection, MoveSpeed * DeltaTime);
//    }
//    else
//    {
//        AddMovementInput(InputDirection, MoveSpeed * DeltaTime);
//    }
//}
void APlayer_Tank::UDMove(float Value)
{
	// 마우스 포인터가 바라보는 것을 정면의 기준으로 삼고 앞 뒤 이동
    if (Value != 0.0f)
    {
        FVector Forward = GetMesh()->GetForwardVector();
        AddMovementInput(Forward, Value);
    }
}

void APlayer_Tank::TurretMove(float Value)
{
    //포탑 상하 회전(SCENE 기준 0~30도)
    if(Value != 0.0f)
    {
        FRotator CurrentRotation = SceneRoot->GetComponentRotation();
        FRotator TargetRotation = FRotator(CurrentRotation.Pitch + Value * TurnSpeed * GetWorld()->GetDeltaSeconds(),
            CurrentRotation.Yaw,
            CurrentRotation.Roll);
        // 상하 회전 제한
        TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch, 0.f, 30.f);
        SceneRoot->SetWorldRotation(TargetRotation);
	}
}

void APlayer_Tank::MousePointerRotation(float delta)
{
    if (TankPlayerController)
    {
        TankPlayerController->bShowMouseCursor = true;

        // 마우스 커서 방향으로 포탑 회전
        FHitResult HitResult;
        if (TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
        {
            FVector ToTarget = HitResult.ImpactPoint - GetMesh()->GetComponentLocation();
            FRotator TargetRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
            FQuat NewRotation = FQuat::Slerp(GetMesh()->GetComponentRotation().Quaternion(),
                TargetRotation.Quaternion(), delta * TurnSpeed);
            GetMesh()->SetWorldRotation(NewRotation);
        }
    }
}
void APlayer_Tank::BaseEnableInput(bool bEnable)
{
    APlayerController* controller = Cast<APlayerController>(GetController());
    if (controller)
    {
        if (bEnable)
            EnableInput(controller);
        else
            DisableInput(controller);

        controller->SetShowMouseCursor(true);
    }
}