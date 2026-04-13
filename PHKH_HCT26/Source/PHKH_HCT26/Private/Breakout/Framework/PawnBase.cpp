#include "Breakout/Framework/PawnBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"
#include "Breakout/Actor/BallBase.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerPaddle"));
	RootComponent = PlayerPaddle;

	PlayerPaddle->SetSimulatePhysics(true);

	PlayerPaddle->BodyInstance.bLockRotation = true;
	PlayerPaddle->BodyInstance.bLockZTranslation = true;
	PlayerPaddle->BodyInstance.bLockYTranslation = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = PlayerPaddle;
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerPaddle)
	{
		PlayerPaddle->OnComponentHit.AddDynamic(this, &APawnBase::OnComponentHit);
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, 
		
	&APawnBase::NewBall, 0.1f, false);
}

void APawnBase::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	ABallBase* HitBall = Cast<ABallBase>(OtherActor);
	
	if (HitBall && HitBall->PingBall)
	{
		FVector CurrentVelocity = HitBall->PingBall->GetPhysicsLinearVelocity();
		FVector NewVelocity = CurrentVelocity.GetSafeNormal() * HitBall->BallSpeed;

		HitBall->PingBall->SetPhysicsLinearVelocity(NewVelocity);
	}
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnBase::Move(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	if (PlayerPaddle && PlayerPaddle->IsSimulatingPhysics())
	{
		PlayerPaddle->WakeAllRigidBodies();
		
		float ImpulseForce = AxisValue * Speed;
		FVector ImpulseVector(ImpulseForce, 0.f, 0.f);

		PlayerPaddle->AddImpulse(ImpulseVector, NAME_None, true);
		return;
	}

	if (MovementComponent)
	{
		AddMovementInput(FVector::RightVector, AxisValue);
	}
}

void APawnBase::NewBall()
{
	if (!BallClass)
	{
		return;
	}

	if (!Arrow)
	{
		return;
	}
	
	FTransform SpawnTransform = Arrow->GetComponentTransform();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ABallBase* SpawnedBall = GetWorld()->SpawnActor<ABallBase>(BallClass, SpawnTransform, SpawnParams);

	if (SpawnedBall)
	{
		Ball = SpawnedBall;
		Ball->IsActive = false;
		Ball->PlayerPaddle = this; 
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("PawnBase: Failed to spawn Ball!"));
	}
}

void APawnBase::Fire(const FInputActionValue& Value)
{
	if (Value.Get<bool>() && Ball && !Ball->IsActive)
	{
		Ball->LaunchBall();
	}
}