// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HCTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PHKH_HCT26_API AHCTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AHCTPlayerController();
	
public:
	void BeginPlay();
};
