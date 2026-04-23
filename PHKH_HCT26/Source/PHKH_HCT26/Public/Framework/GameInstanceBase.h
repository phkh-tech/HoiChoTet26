#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceBase.generated.h"

UCLASS()
class PHKH_HCT26_API UGameInstanceBase : public UGameInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Stats")
    int32 Lifes = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Stats")
    int32 HighScores = 0;
};