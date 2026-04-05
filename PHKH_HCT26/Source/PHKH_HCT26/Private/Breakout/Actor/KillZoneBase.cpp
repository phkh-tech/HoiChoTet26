#include "Breakout/Actor/KillZoneBase.h"
#include "Breakout/Actor/BallBase.h"

AKillZoneBase::AKillZoneBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZoneBox"));
	BoxComponent->InitBoxExtent(FVector(200.f, 200.f, 50.f));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
    
	BoxComponent->SetGenerateOverlapEvents(true);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKillZoneBase::OnBoxBeginOverlap);
}

void AKillZoneBase::BeginPlay()
{
	Super::BeginPlay();
}

void AKillZoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKillZoneBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									 bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	// 1. Try to cast the overlapping actor to your Ball class
	ABallBase* Ball = Cast<ABallBase>(OtherActor);

	if (Ball)
	{
		// 2. Call your custom death function which handles GameMode/GameInstance logic
		Ball->HandleBallDeath();
	}
	else
	{
		// 3. If it's not the ball (like a stray physics prop), just destroy it normally
		OtherActor->Destroy();
	}
}