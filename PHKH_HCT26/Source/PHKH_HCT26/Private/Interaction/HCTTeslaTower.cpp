#include "Interaction/HCTTeslaTower.h"

AHCTTeslaTower::AHCTTeslaTower()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ReleaseElectricityEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ReleaseElectricityEffect"));
	ReleaseElectricityEffect->SetupAttachment(SceneRoot);

	RangeofEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RangeofEffect"));
	RangeofEffect->SetupAttachment(SceneRoot);

	CachedPlayerPawn = nullptr;
}

void AHCTTeslaTower::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		CachedPlayerPawn = PlayerController->GetPawn();
	}
}

void AHCTTeslaTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (RangeofEffect)
	{
		RangeofEffect->SetFloatParameter(FName("Radius"), CastingRange);
		RangeofEffect->SetFloatParameter(FName("Height"), 100.f);
		RangeofEffect->SetColorParameter(FName("Color"), FLinearColor::FromSRGBColor(FColor(48, 41, 255)));
	}
}

void AHCTTeslaTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!ReleaseElectricityEffect || !CachedPlayerPawn)
		return;

	if (ReleaseElectricityEffect != nullptr && CachedPlayerPawn != nullptr) 
	{ 
		const FVector TowerLocation = GetActorLocation();
		const FVector PlayerLocation = CachedPlayerPawn->GetActorLocation();
		const float Distance = FVector::Dist(TowerLocation, PlayerLocation);

		// Check if player is within range
		if (Distance <= CastingRange)
		{
			ReleaseElectricityEffect->SetVariablePosition(FName("PositionTarget"), PlayerLocation);
		}
	}
}
