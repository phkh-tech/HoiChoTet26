// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HCTButtonBase.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureKhiBatDauOverlap, AActor*, OverlappingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureKhiHetOverlap, AActor*, OverlappingActor);

UCLASS()
class PHKH_HCT26_API AHCTButtonBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCTButtonBase();
	
	UPROPERTY(BlueprintAssignable, Category=HCT2026)
	FSignatureKhiBatDauOverlap EnterStore;
	
	UPROPERTY(BlueprintAssignable, Category=HCT2026)
	FSignatureKhiHetOverlap ExitStore;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionComponent;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
