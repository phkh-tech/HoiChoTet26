// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HCTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PHKH_HCT26_API AHCTGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHCTGameMode();
	
	virtual void BeginPlay() override;
};
