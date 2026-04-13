#include "Interaction/HCTButtonBase.h"
#include "Components/BoxComponent.h"
#include "Framework/HCTPawn.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

AHCTButtonBase::AHCTButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create root
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// Create and configure box collision
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
}

void AHCTButtonBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHCTButtonBase::OnBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AHCTButtonBase::OnEndOverlap);
}

void AHCTButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCTButtonBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		EnterShop.Broadcast(OtherActor);
	}
}

void AHCTButtonBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		ExitShop.Broadcast(OtherActor);
	}
}
