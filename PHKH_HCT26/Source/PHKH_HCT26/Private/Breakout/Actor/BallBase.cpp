#include "Breakout/Actor/BallBase.h"
#include "Components/ArrowComponent.h"
#include "Breakout/Framework/PawnBase.h"
#include "Breakout/Framework/GameInstanceBase.h"
#include "Breakout/Framework/MyGameModeBase.h"

ABallBase::ABallBase()
{
    PrimaryActorTick.bCanEverTick = true;

    PingBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PingBall"));
    RootComponent = PingBall;

    PingBall->SetSimulatePhysics(true);
    PingBall->BodyInstance.bLockRotation = true;
    PingBall->BodyInstance.bLockZTranslation = true;
}

void ABallBase::BeginPlay()
{
    Super::BeginPlay();
    PlayerPaddle = Cast<APawnBase>(GetOwner());
}

void ABallBase::Destroyed()
{
    Super::Destroyed();
}

void ABallBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdatePosition();
    VelocityAndAngle();
}

void ABallBase::UpdatePosition()
{
    if (!IsActive && PlayerPaddle)
    {
        if (const UArrowComponent* Arrow = PlayerPaddle->FindComponentByClass<UArrowComponent>())
        {
            SetActorLocation(Arrow->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);
        }
    }
}

void ABallBase::LaunchBall()
{
    if (!IsActive && PingBall)
    {
        IsActive = true;

        FVector LaunchVector(-1500.f, 1500.f, 0.f);
        PingBall->AddImpulse(LaunchVector, NAME_None, true);
    }
}

void ABallBase::VelocityAndAngle()
{
    if (!PingBall) return;

    FVector Velocity = PingBall->GetPhysicsLinearVelocity();
    float Speed = Velocity.Size();

    FVector Clamped = Velocity.GetClampedToSize(BallSpeed, BallSpeed);

    FRotator Offset(0.f, -45.f, 0.f);
    FVector Rotated = Offset.RotateVector(Clamped);

    float Yaw = FMath::RoundToFloat(Rotated.Rotation().Yaw / 90.f) * 90.f;

    FVector FinalDir = Offset.UnrotateVector(FRotator(0.f, Yaw, 0.f).Vector());
    PingBall->SetPhysicsLinearVelocity(FinalDir * Speed);
}

void ABallBase::HandleBallDeath()
{
    AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
    UGameInstanceBase* GI = Cast<UGameInstanceBase>(GetGameInstance());

    if (GM && GI)
    {
        GM->Lifes--;
        GI->Lifes = GM->Lifes;

        UE_LOG(LogTemp, Warning, TEXT("Current Lifes: %d"), GM->Lifes);

        GM->LifeLoss();
    }

    Destroy();
}