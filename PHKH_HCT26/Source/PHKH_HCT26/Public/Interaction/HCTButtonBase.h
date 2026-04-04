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
	AHCTButtonBase();

	UPROPERTY(BlueprintAssignable, Category="Button Events")
	FSignatureKhiBatDauOverlap EnterShop;

	UPROPERTY(BlueprintAssignable, Category="Button Events")
	FSignatureKhiHetOverlap ExitShop;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* CollisionComponent;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
