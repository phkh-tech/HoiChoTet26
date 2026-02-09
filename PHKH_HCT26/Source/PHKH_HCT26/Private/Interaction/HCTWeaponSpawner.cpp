// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HCTWeaponSpawner.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AHCTWeaponSpawner::AHCTWeaponSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCTWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCTWeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCTWeaponSpawner::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (ExplosionEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	}
}
