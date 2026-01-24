// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "HCT_HUD.generated.h"

class UUserWidget;

UCLASS()
class PHKH_HCT26_API AHCT_HUD : public AHUD
{
	GENERATED_BODY()
	
	AHCT_HUD();
	
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI HCT 2026")
	TSubclassOf<UUserWidget> WBP_HCT26;

protected:

	UPROPERTY()
	UUserWidget* HUDWidgetInstance;
};
