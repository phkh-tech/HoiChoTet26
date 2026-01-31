// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HCTPossessableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHCTPossessableInterface : public UInterface
{
	GENERATED_BODY()
};

class PHKH_HCT26_API IHCTPossessableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// Called when controller wants the pawn to change material
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Possession")
	void ChangeMaterial();
};
