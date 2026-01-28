// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTPlayerController.h"
#include "EnhancedInputComponent.h"
#include "PHKH_HCT26/PHKH_HCT26.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"


AHCTPlayerController::AHCTPlayerController()
{
}

void AHCTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	
	UE_LOG(LogHCT2026, Warning, TEXT("Start HCTPlayerController"));
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (PossessMappingContext)
		{
			Subsystem->AddMappingContext(PossessMappingContext, 0);
		}
	}
	PossesNearestPawns();
}

void AHCTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Move);
			UE_LOG(LogTemp, Warning, TEXT("Move Action."));
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Look);
			UE_LOG(LogTemp, Warning, TEXT("Look Action."));
		}
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
		
		// Add movement in right and forward directions
		CurrentPawn->AddMovementInput(Right, MovementValue.X);
		CurrentPawn->AddMovementInput(Forward, MovementValue.Y);
	}
}

void AHCTPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	if (APawn* CurrentPawn = GetPawn())
	{
		CurrentPawn->AddControllerYawInput(LookAxis.X);
		CurrentPawn->AddControllerPitchInput(LookAxis.Y);
	}
}

void AHCTPlayerController::PossesNearestPawns() const
{
	TArray<AHCTPawn*> PossessablePawns;
	PossessablePawns.Empty();
	
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("GatherPossessablePawns: World is null."));
		return;
	}
}

