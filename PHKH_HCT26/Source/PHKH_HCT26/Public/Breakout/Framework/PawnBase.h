#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PawnBase.generated.h"

class UArrowComponent;
class ABallBase;
class UStaticMeshComponent;

UCLASS()
class PHKH_HCT26_API APawnBase : public APawn
{
	GENERATED_BODY()
    
public: 
	virtual void Tick(float DeltaTime) override;
    
	APawnBase();

	void Move(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
    
	UFUNCTION(BlueprintCallable, Category = "Game Events")
	void NewBall();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 450.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* MovementComponent;

protected:
    
	virtual void BeginPlay() override;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlayerPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
	TSubclassOf<ABallBase> BallClass;

	UPROPERTY(BlueprintReadOnly, Category = "Ball")
	ABallBase* Ball;
};