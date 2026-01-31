// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PHKH_HCT26/PHKH_HCT26.h"


UE_DEFINE_GAMEPLAY_TAG(Possession, "Possession");

// Sets default values
AHCTPawn::AHCTPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	RootComponent = PawnMesh;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
	
	GamePlayTag.AddTag(Possession);

}

// Called when the game starts or when spawned
void AHCTPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogHCT2026, Warning, TEXT("Start HCTPawn"));
	
	if (DefaultMaterial)
	{
		PawnMesh->SetMaterial(0, DefaultMaterial);
	}
	
}

// Called every frame
void AHCTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Interface function: toggles material
void AHCTPawn::ChangeMaterial_Implementation()
{
	if (!PawnMesh) return;

	if (bUsingAlternateMaterial)
	{
		if (DefaultMaterial)
		{
			PawnMesh->SetMaterial(0, DefaultMaterial);
		}
	}
	else
	{
		if (AlternateMaterial)
		{
			PawnMesh->SetMaterial(0, AlternateMaterial);
		}
	}

	bUsingAlternateMaterial = !bUsingAlternateMaterial;

	UE_LOG(LogHCT2026, Warning, TEXT("%s changed material"), *GetName());
}

