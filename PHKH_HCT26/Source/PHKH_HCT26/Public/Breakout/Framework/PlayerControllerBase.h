#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PlayerControllerBase.generated.h"

class UInputAction;
class UInputMappingContext;
class UFloatingPawnMovement;

UCLASS()
class PHKH_HCT26_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerBase();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void Move(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* MoveMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* FireMappingContext;
};