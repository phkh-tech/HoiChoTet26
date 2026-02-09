// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "HCTTeslaTower.generated.h"

UCLASS()
class PHKH_HCT26_API  AHCTTeslaTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCTTeslaTower();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VFX)
	UNiagaraComponent* ReleaseElectricityEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VFX)
	UNiagaraComponent* RangeofEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Range")
	float CastingRange = 500.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(BlueprintReadOnly, Category=Player)
	APawn* CachedPlayerPawn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
