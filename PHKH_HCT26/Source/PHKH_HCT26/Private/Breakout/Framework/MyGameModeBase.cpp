#include "Breakout/Framework/MyGameModeBase.h"
#include "Breakout/Framework/PawnBase.h"
#include "Breakout/Framework/GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Breakout/Widget/WidgetBase.h"
#include "Framework/HCTPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
    DefaultPawnClass = APawnBase::StaticClass();
    PlayerControllerClass = AHCTPlayerController::StaticClass();

    AsPingGameInstance = nullptr;
    HUDWidget = nullptr;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    AsPingGameInstance = Cast<UGameInstanceBase>(GetGameInstance());
    
    if (AsPingGameInstance)
    {
        if (AsPingGameInstance->Lifes <= 0) 
        {
            AsPingGameInstance->Lifes = 3;
        }
        this->Lifes = AsPingGameInstance->Lifes;
    }

    if (HUDWidgetClass) 
    {
        HUDWidget = CreateWidget<UWidgetBase>(GetWorld(), HUDWidgetClass);

        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->UpdateLivesDisplay(this->Lifes);
            HUDWidget->UpdateHighScoresDisplay(0);
            
            if (AsPingGameInstance)
            {
                HUDWidget->UpdateWinScoresDisplay(AsPingGameInstance->HighScores);
            }
        }
    }
}

void AMyGameModeBase::UpdateScore(int32 Score)
{
    CurrentScore += Score;
    if (CurrentScore < 0) CurrentScore = 0;

    if (AsPingGameInstance)
    {
        if (CurrentScore > AsPingGameInstance->HighScores)
        {
            AsPingGameInstance->HighScores = CurrentScore;
            if (HUDWidget)
            {
                HUDWidget->UpdateWinScoresDisplay(AsPingGameInstance->HighScores);
            }
        }
    }
    if (HUDWidget)
    {
        HUDWidget->UpdateHighScoresDisplay(CurrentScore);
    }
}

void AMyGameModeBase::UpdateHighScores()
{
    if (AsPingGameInstance && CurrentScore > AsPingGameInstance->HighScores)
    {
        AsPingGameInstance->HighScores = CurrentScore;
    }
}

void AMyGameModeBase::LifeLoss()
{
    if (Lifes <= 0)
    {
        GameOver();
    }
    //else{if (AsPingGameInstance){AsPingGameInstance->Lifes = this->Lifes;}UGameplayStatics::OpenLevel(GetWorld(), FName("Sandbox"));}
}

void AMyGameModeBase::GameOver()
{
    UpdateHighScores();

    if (HUDWidget)
    {
        HUDWidget->UpdateLivesDisplay(Lifes);
        HUDWidget->UpdateHighScoresDisplay(CurrentScore);
    }

    IsGameOver = true;

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->bShowMouseCursor = true;
        PC->bEnableClickEvents = true;
        PC->bEnableMouseOverEvents = true;

        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);
    }
}

void AMyGameModeBase::ResetGame()
{
    if (AsPingGameInstance)
    {
        AsPingGameInstance->Lifes = 3;      
        AsPingGameInstance->HighScores = 0;
    }
    
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->bShowMouseCursor = false;
        PC->bEnableClickEvents = false;
        PC->bEnableMouseOverEvents = false;

        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->FlushPressedKeys();
    }
    UGameplayStatics::OpenLevel(GetWorld(), FName("Sandbox"));
}