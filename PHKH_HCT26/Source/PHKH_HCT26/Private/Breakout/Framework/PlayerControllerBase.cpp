#include "Breakout/Framework/PlayerControllerBase.h"
#include "Breakout/Framework/PawnBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerControllerBase::APlayerControllerBase()
{
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
	   ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		
		if (MoveMappingContext)
		{
			Subsystem->AddMappingContext(MoveMappingContext, 0);
		}

		if (FireMappingContext)
		{
			Subsystem->AddMappingContext(FireMappingContext, 0);
		}
	}
}

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		if (MoveMappingContext) Subsystem->AddMappingContext(MoveMappingContext, 0);
		if (FireMappingContext) Subsystem->AddMappingContext(FireMappingContext, 0);
	}
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,
				this,&APlayerControllerBase::Move);
		}

		if (FireAction)
		{
			EnhancedInput->BindAction(FireAction,ETriggerEvent::Triggered,
				this,&APlayerControllerBase::Fire);
		}
	}
}

void APlayerControllerBase::Move(const FInputActionValue& Value)
{
	if (APawnBase* ControlledPawn = Cast<APawnBase>(GetPawn()))
	{
		ControlledPawn->Move(Value);
	}
}

void APlayerControllerBase::Fire(const FInputActionValue& Value)
{
	if (APawnBase* ControlledPawn = Cast<APawnBase>(GetPawn()))
	{
		ControlledPawn->Fire(Value);
	}
}