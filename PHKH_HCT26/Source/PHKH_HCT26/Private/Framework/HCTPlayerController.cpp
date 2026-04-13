#include "Framework/HCTPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/HCTPawn.h"
#include "Breakout/Framework/PawnBase.h" 
#include "HCTPossessableInterface.h"

AHCTPlayerController::AHCTPlayerController() {}

void AHCTPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (DefaultMappingContext)
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
    
    const FGameplayTag PossessionTag = FGameplayTag::RequestGameplayTag(FName("Possession"));
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHCTPawn::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (AHCTPawn* HCTPawn = Cast<AHCTPawn>(Actor))
        {
            if (HCTPawn->GamePlayTag.HasTag(PossessionTag))
            {
                CachedPossessionPawns.Add(HCTPawn);
            }
        }
    }
    
    if (CachedPossessionPawns.Num() > 0 && CachedPossessionPawns[0].IsValid())
    {
        Possess(CachedPossessionPawns[0].Get());
    }
}

void AHCTPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // General Actions
        if (MoveAction) EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Move);
        if (LookAction) EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::Look);
        if (PossessAction) EnhancedInput->BindAction(PossessAction, ETriggerEvent::Started, this, &AHCTPlayerController::HandlePossessAction);
        if (ChangeMaterial) EnhancedInput->BindAction(ChangeMaterial, ETriggerEvent::Started, this, &AHCTPlayerController::HandleChangeMaterial);

        // Paddle Specific Actions
        if (PaddleMoveAction) EnhancedInput->BindAction(PaddleMoveAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::PaddleMove);
        if (PaddleFireAction) EnhancedInput->BindAction(PaddleFireAction, ETriggerEvent::Triggered, this, &AHCTPlayerController::PaddleFire);
    }
}

void AHCTPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (InPawn && InPawn->IsA(APawnBase::StaticClass())) // Assuming APawnBase is the Paddle
        {
            if (PaddleMappingContext) Subsystem->AddMappingContext(PaddleMappingContext, 1);
            if (PaddleFireContext) Subsystem->AddMappingContext(PaddleFireContext, 1);
        }
        else
        {
            if (PaddleMappingContext) Subsystem->RemoveMappingContext(PaddleMappingContext);
            if (PaddleFireContext)    Subsystem->RemoveMappingContext(PaddleFireContext);
        }
    }
}

void AHCTPlayerController::PossessNextPawnWithTag(const FGameplayTag& TagToFind)
{
    if (CachedPossessionPawns.Num() == 0) return;

    CurrentPawnIndex = (CurrentPawnIndex + 1) % CachedPossessionPawns.Num();

    if (CachedPossessionPawns[CurrentPawnIndex].IsValid())
    {
        AHCTPawn* NextPawn = CachedPossessionPawns[CurrentPawnIndex].Get();
        SetViewTargetWithBlend(NextPawn, 0.3f);
        Possess(NextPawn);
    }
}

void AHCTPlayerController::HandlePossessAction(const FInputActionValue& Value)
{
    PossessNextPawnWithTag(FGameplayTag::RequestGameplayTag(FName("Possession")));
}

void AHCTPlayerController::PaddleMove(const FInputActionValue& Value)
{
    if (APawnBase* ControlledPawn = Cast<APawnBase>(GetPawn()))
    {
        ControlledPawn->Move(Value);
    }
}

void AHCTPlayerController::PaddleFire(const FInputActionValue& Value)
{
    if (APawnBase* ControlledPawn = Cast<APawnBase>(GetPawn()))
    {
        ControlledPawn->Fire(Value);
    }
}

void AHCTPlayerController::Move(const FInputActionValue& Value)
{
    const FVector2D MovementValue = Value.Get<FVector2D>();
    if (APawn* CurrentPawn = GetPawn())
    {
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

void AHCTPlayerController::HandleChangeMaterial(const FInputActionValue& Value)
{
    APawn* CurrentPawn = GetPawn();
    if (CurrentPawn && CurrentPawn->GetClass()->ImplementsInterface(UHCTPossessableInterface::StaticClass()))
    {
        IHCTPossessableInterface::Execute_ChangeMaterial(CurrentPawn);
    }
}