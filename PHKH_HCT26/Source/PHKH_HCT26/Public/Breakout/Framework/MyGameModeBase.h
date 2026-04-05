#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UUserWidget;
class UGameInstanceBase;
class UWidgetBase;

UCLASS()
class PHKH_HCT26_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

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
	void LifeLoss();

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameOver();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Rules")
	void WinningCondition();

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void ResetGame();

protected:
	UPROPERTY()
	UGameInstanceBase* AsPingGameInstance;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UWidgetBase* HUDWidget;
};