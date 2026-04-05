#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBlock.generated.h"

UCLASS()
class PHKH_HCT26_API ABaseBlock : public AActor
{
	GENERATED_BODY()

public:
	ABaseBlock();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BlockMesh;

	UFUNCTION()
	void OnComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};