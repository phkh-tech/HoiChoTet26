// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HCT_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PHKH_HCT26_API AHCT_HUD : public AHUD
{
	GENERATED_BODY()
	
	AHCT_HUD();
	
public:
	virtual void BeginPlay() override;
};
