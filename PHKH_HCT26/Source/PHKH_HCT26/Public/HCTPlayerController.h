// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
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
	void SetupInputComponent() override;
	
protected:
	void BeginPlay();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	
private:
	
	UPROPERTY()
	APawn* SavedPawn = nullptr;
	
};
