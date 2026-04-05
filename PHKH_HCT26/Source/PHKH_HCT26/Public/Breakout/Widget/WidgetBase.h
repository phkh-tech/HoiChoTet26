#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UCLASS()
class PHKH_HCT26_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateLivesDisplay(int32 NewLives);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHighScoresDisplay(int32 NewHighScore);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWinScoresDisplay(int32 WinScore);
};