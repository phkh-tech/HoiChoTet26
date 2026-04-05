#include "Breakout/Actor/BaseBlock.h"
#include "Breakout/Actor/BallBase.h"
#include "Kismet/GameplayStatics.h"
#include "Breakout/Framework/MyGameModeBase.h"

ABaseBlock::ABaseBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;

	BlockMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BlockMesh->SetNotifyRigidBodyCollision(true);
}

void ABaseBlock::BeginPlay()
{
	Super::BeginPlay();

	BlockMesh->OnComponentHit.AddDynamic(
		this,
		&ABaseBlock::OnComponentHit
	);
}

void ABaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBlock::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	ABallBase* Ball = Cast<ABallBase>(OtherActor);

	if (Ball && Ball->PingBall)
	{
		ABallBase* HitBall = Cast<ABallBase>(OtherActor);

		if (HitBall && HitBall->PingBall)
		{

			FVector CurrentVelocity = HitBall->PingBall->GetPhysicsLinearVelocity();
			FVector NewVelocity = CurrentVelocity.GetSafeNormal() * HitBall->BallSpeed;

			HitBall->PingBall->SetPhysicsLinearVelocity(NewVelocity);

			AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());

			if (MyGameMode)
			{
				MyGameMode->UpdateScore(1);

				// Get all blocks currently in the level
				TArray<AActor*> FoundBlocks;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseBlock::StaticClass(), FoundBlocks);

				// IMPORTANT: If count is 1, the ONLY block left is the one we just hit.
				if (FoundBlocks.Num() == 1 && FoundBlocks[0] == this)
				{
					UE_LOG(LogTemp, Warning, TEXT("WINNING CONDITION TRIGGERED!"));
					MyGameMode->WinningCondition();
				}
			}

			// Now it is safe to destroy
			this->Destroy();
		}
	}
}