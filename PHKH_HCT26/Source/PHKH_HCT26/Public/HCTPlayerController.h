// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "HCTPawn.h"
#include "InputActionValue.h" 
#include "GameFramework/PlayerController.h"
#include "HCTPlayerController.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;

UCLASS() 
class PHKH_HCT26_API AHCTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AHCTPlayerController();
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
protected:

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void PossesNearestPawns() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* PossessMappingContext;
	
	
};
