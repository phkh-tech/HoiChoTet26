// Fill out your copyright notice in the Description page of Project Settings.

#include "PHKH_HCT26/Public/HCTPlayerController.h"
#include "EnhancedInputComponent.h"
#include "PHKH_HCT26/PHKH_HCT26.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "HCTPawn.h"
#include "HCTPossessableInterface.h"

AHCTPlayerController::AHCTPlayerController()
{
}

void AHCTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	
	UE_LOG(LogHCT2026, Warning, TEXT("Start HCTPlayerController"));
	
	// Add input mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (PossessMappingContext)
		{
			Subsystem->AddMappingContext(PossessMappingContext, 0);
		}
	}

	// Cache all pawns with the "Possession" tag
	FGameplayTag PossessionTag = FGameplayTag::RequestGameplayTag(FName("Possession"));
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHCTPawn::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AHCTPawn* HCTPawn = Cast<AHCTPawn>(Actor))
		{
			if (HCTPawn->GamePlayTag.HasTag(PossessionTag))
			{
				CachedPossessionPawns.Add(HCTPawn);
				UE_LOG(LogHCT2026, Warning, TEXT("Found pawn with Possession tag: %s"), *HCTPawn->GetName());
			}
		}
	}

	// Possess the first pawn if available
	if (CachedPossessionPawns.Num() > 0 && CachedPossessionPawns[0].IsValid())
	{
		Possess(CachedPossessionPawns[0].Get());
		UE_LOG(LogHCT2026, Warning, TEXT("Initially possessed pawn: %s"), *CachedPossessionPawns[0]->GetName());
	}
}

void AHCTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Move);
			UE_LOG(LogTemp, Warning, TEXT("Move Action bound."));
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Look);
			UE_LOG(LogTemp, Warning, TEXT("Look Action bound."));
		}
		if (PossessAction)
		{
			// Mouse button triggers possession
			EnhancedInput->BindAction(PossessAction, ETriggerEvent::Started, this, &AHCTPlayerController::HandlePossessAction);
			UE_LOG(LogTemp, Warning, TEXT("Possess Action bound to mouse button."));
		}
		if (ChangeMaterial)
			EnhancedInput->BindAction(ChangeMaterial, ETriggerEvent::Started, this, &AHCTPlayerController::HandleChangeMaterial);
	}
}

void AHCTPlayerController::HandlePossessAction(const FInputActionValue& Value)
{
	PossessNextPawnWithTag(FGameplayTag::RequestGameplayTag(FName("Possession")));
}

void AHCTPlayerController::PossessNextPawnWithTag(const FGameplayTag& TagToFind)
{

	// Move to next pawn index (loop back to 0 if at end)
	CurrentPawnIndex = (CurrentPawnIndex + 1) % CachedPossessionPawns.Num();

	// Get the next valid pawn
	if (CachedPossessionPawns[CurrentPawnIndex].IsValid())
	{
		AHCTPawn* NextPawn = CachedPossessionPawns[CurrentPawnIndex].Get();

		// Optional smooth camera blend
		SetViewTargetWithBlend(NextPawn, 0.3f); // 0.3s smooth transition

		// Possess the next pawn
		Possess(NextPawn);

		UE_LOG(LogHCT2026, Warning, TEXT("Switched possession to pawn: %s"), *NextPawn->GetName());
	}
	else
	{
		UE_LOG(LogHCT2026, Warning, TEXT("Invalid pawn reference in cache."));
	}
}

void AHCTPlayerController::HandleChangeMaterial(const FInputActionValue& Value)
{
	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn && CurrentPawn->GetClass()->ImplementsInterface(UHCTPossessableInterface::StaticClass()))
	{
		IHCTPossessableInterface::Execute_ChangeMaterial(CurrentPawn);
	}
}

void AHCTPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();
	if (APawn* CurrentPawn = GetPawn())
	{
		// Use controller yaw only so movement is relative to where the controller is facing
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		CurrentPawn->AddMovementInput(Right, MovementValue.X);
		CurrentPawn->AddMovementInput(Forward, MovementValue.Y);
	}
}

void AHCTPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	AddYawInput(LookAxis.X);
	AddPitchInput(LookAxis.Y);
}


