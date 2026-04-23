// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniGameManager/BreakouBallManager.h"
#include "Breakout/Framework/PawnBase.h"
#include "Framework/GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ABreakouBallManager::ABreakouBallManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABreakouBallManager::BeginPlay()
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
}

void ABreakouBallManager::UpdateScore(int32 Score)
{
	if (IsGameOver) return;
	
	CurrentScore += Score;
	
	if (CurrentScore < 0)
	{
		CurrentScore = 0;
	}

	if (BallGameInstance && CurrentScore > BallGameInstance->HighScores)
	{
		BallGameInstance->HighScores = CurrentScore;
		OnScoreChanged(CurrentScore);
	}
}

void ABreakouBallManager::UpdateHighScores()
{
	if (BallGameInstance && CurrentScore > BallGameInstance->HighScores)
	{
		BallGameInstance->HighScores = CurrentScore;
	}
}

void ABreakouBallManager::LifeLost()
{
	if (IsGameOver) return;
	
	Lifes--;
		
	if (BallGameInstance)
	{
		BallGameInstance->Lifes = Lifes;
		OnLifeChanged(Lifes);
	}
	if (Lifes <= 0)
	{
		GameOver();
	}
	else
	{
		RespawnBall();
	}
}

void ABreakouBallManager::RespawnBall()
{
	APawnBase* PlayerPawn = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerPawn)
	{
		FTimerHandle RespawnTimer;
		GetWorldTimerManager().SetTimer(RespawnTimer, PlayerPawn, &APawnBase::NewBall, 1.0f, false);
	}
}


void ABreakouBallManager::GameOver()
{
	IsGameOver = true;
}

void ABreakouBallManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

