// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakouBallManager.generated.h"

class UGameInstanceBase;
class APawnBase;

UCLASS()
class PHKH_HCT26_API ABreakouBallManager : public AActor
{
	GENERATED_BODY()

public:
	ABreakouBallManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Stats")
	int32 CurrentScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Stats")
	int32 Lifes = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool IsGameOver = false;
	
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void UpdateScore(int32 Score);

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void UpdateHighScores();
	
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void LifeLost();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Rules")
	void OnScoreChanged(int32 NewScore);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Rules")
	void OnLifeChanged(int32 NewLifes);
	
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void RespawnBall();
	
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameOver();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGameInstanceBase* BallGameInstance;

public:
	virtual void Tick(float DeltaTime) override;
};
