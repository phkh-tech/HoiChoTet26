// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "HCTPawn.h"
#include "GameplayTagContainer.h"
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
	virtual void PossessNextPawnWithTag(const FGameplayTag& TagToFind);
	
protected:
	void HandlePossessAction(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void HandleChangeMaterial(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* PossessAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* ChangeMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* PossessMappingContext;

private:
	// Index to track which pawn is currently possessed
	int32 CurrentPawnIndex = 0;

	// Cached pawns with the possession tag
	TArray<TWeakObjectPtr<AHCTPawn>> CachedPossessionPawns;
};
