#include "Interaction/HCTButtonBase.h"
#include "Components/BoxComponent.h"
#include "HCTPawn.h"
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
	if (!OtherActor)
		return;

	bool bIsValidOverlap = false;

	// Check if the overlapping actor is your custom HCTPawn
	if (Cast<AHCTPawn>(OtherActor))
	{
		bIsValidOverlap = true;
	}

	// Or if it’s a Character (e.g., BP_ThirdPersonCharacter)
	else if (Cast<ACharacter>(OtherActor))
	{
		bIsValidOverlap = true;
	}

	if (bIsValidOverlap)
	{
		// Display message on screen (like Print String)
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("Hello"));
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, Msg);
		}

		// Trigger Blueprint delegate
		EnterShop.Broadcast(OtherActor);
	}
}

void AHCTButtonBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	bool bIsValidOverlap = false;

	if (Cast<AHCTPawn>(OtherActor))
	{
		bIsValidOverlap = true;
	}
	else if (Cast<ACharacter>(OtherActor))
	{
		bIsValidOverlap = true;
	}

	if (bIsValidOverlap)
	{
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("Goodbye"));
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Msg);
		}

		ExitShop.Broadcast(OtherActor);
	}
}
