#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "HCTPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class AHCTPawn;

UCLASS()
class PHKH_HCT26_API AHCTPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AHCTPlayerController();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* InPawn) override;
    
    virtual void PossessNextPawnWithTag(const FGameplayTag& TagToFind);

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void HandlePossessAction(const FInputActionValue& Value);
    void HandleChangeMaterial(const FInputActionValue& Value);
    
    void PaddleMove(const FInputActionValue& Value);
    void PaddleFire(const FInputActionValue& Value);

    /** Input Actions */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|General")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|General")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|General")
    UInputAction* PossessAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|General")
    UInputAction* ChangeMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|Paddle")
    UInputAction* PaddleMoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|Paddle")
    UInputAction* PaddleFireAction;

    /** Mapping Contexts */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|Contexts")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|Contexts")
    UInputMappingContext* PaddleMappingContext;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input|Contexts")
    UInputMappingContext* PaddleFireContext;

private:
    int32 CurrentPawnIndex = 0;
    TArray<TWeakObjectPtr<AHCTPawn>> CachedPossessionPawns;
};