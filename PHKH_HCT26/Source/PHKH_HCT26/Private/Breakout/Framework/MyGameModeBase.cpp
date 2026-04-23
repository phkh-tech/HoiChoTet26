#include "Breakout/Framework/MyGameModeBase.h"
#include "Breakout/Framework/PawnBase.h"
#include "Framework/GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Breakout/Widget/WidgetBase.h"
#include "Framework/HCTPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
    DefaultPawnClass = APawnBase::StaticClass();
    PlayerControllerClass = AHCTPlayerController::StaticClass();

    BallGameInstance = nullptr;
    HUDWidget = nullptr;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    BallGameInstance = Cast<UGameInstanceBase>(GetGameInstance());
    
    if (BallGameInstance)
    {
        if (BallGameInstance->Lifes <= 0) 
        {
            BallGameInstance->Lifes = 3;
        }
        this->Lifes = BallGameInstance->Lifes;
    }

    if (HUDWidgetClass) 
    {
        HUDWidget = CreateWidget<UWidgetBase>(GetWorld(), HUDWidgetClass);

        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->UpdateLivesDisplay(this->Lifes);
            HUDWidget->UpdateHighScoresDisplay(0);
            
            if (BallGameInstance)
            {
                HUDWidget->UpdateWinScoresDisplay(BallGameInstance->HighScores);
            }
        }
    }
}

void AMyGameModeBase::UpdateScore(int32 Score)
{
    CurrentScore += Score;
    if (CurrentScore < 0) CurrentScore = 0;

    if (BallGameInstance)
    {
        if (CurrentScore > BallGameInstance->HighScores)
        {
            BallGameInstance->HighScores = CurrentScore;
            if (HUDWidget)
            {
                HUDWidget->UpdateWinScoresDisplay(BallGameInstance->HighScores);
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
    if (BallGameInstance && CurrentScore > BallGameInstance->HighScores)
    {
        BallGameInstance->HighScores = CurrentScore;
    }
}

void AMyGameModeBase::LifeLoss()
{
    if (Lifes <= 0)
    {
        GameOver();
    }
     else{
        if (BallGameInstance)
       {
           BallGameInstance->Lifes = this->Lifes;
       }
        UGameplayStatics::OpenLevel(GetWorld(), FName("Sandbox"));
   }
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
    if (BallGameInstance)
    {
        BallGameInstance->Lifes = 3;      
        BallGameInstance->HighScores = 0;
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