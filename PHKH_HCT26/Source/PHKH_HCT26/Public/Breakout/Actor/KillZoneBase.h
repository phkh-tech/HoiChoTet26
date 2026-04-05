#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "KillZoneBase.generated.h"

UCLASS()
class PHKH_HCT26_API AKillZoneBase : public AActor
{
	GENERATED_BODY()

public:
	AKillZoneBase();

protected:
	virtual void BeginPlay() override;

	// Box collision component used as trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxComponent;

	// Overlap begin handler
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						  bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
};