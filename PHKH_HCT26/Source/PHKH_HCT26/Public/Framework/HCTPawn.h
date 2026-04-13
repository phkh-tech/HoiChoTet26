// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Pawn.h"
#include "HCTPossessableInterface.h" 
#include "HCTPawn.generated.h"

class USphereComponent;
class UInputAction;
class UFloatingPawnMovement;
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Possession);


UCLASS()
class PHKH_HCT26_API AHCTPawn : public APawn, public IHCTPossessableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHCTPawn();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Game Tag")
	FGameplayTagContainer GamePlayTag;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;
	
	
	// Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInterface* AlternateMaterial;

	// Track state
	bool bUsingAlternateMaterial = false;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
