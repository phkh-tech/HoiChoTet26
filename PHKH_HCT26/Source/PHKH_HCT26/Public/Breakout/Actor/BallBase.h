#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBase.generated.h"

class UStaticMeshComponent;
class APawnBase;

UCLASS()
class PHKH_HCT26_API ABallBase : public AActor
{
	GENERATED_BODY()

public:
	ABallBase();

	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void UpdatePosition();

	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void LaunchBall();

	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void VelocityAndAngle();

	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void HandleBallDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameStats")
	double BallSpeed = 1000.0f;

	UPROPERTY(BlueprintReadWrite, Category = "GameStats")
	bool IsActive = false;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawnBase> PlayerPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PingBall;
	
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};