// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RTDAISpawnPoint.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARTDAISpawnPoint::ARTDAISpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Spline = nullptr;
}

// Called when the game starts or when spawned
void ARTDAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	if (UKismetSystemLibrary::IsServer(this))
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle,this,&ARTDAISpawnPoint::SpawnAI,1.f,false);
	}
}

// Called every frame
void ARTDAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTDAISpawnPoint::SpawnAI()
{
	if (AIToSpawn.LoadSynchronous())
	{
		ASimpleRacingTechDemoAI* AI = GetWorld()->SpawnActorDeferred<ASimpleRacingTechDemoAI>(
		   AIToSpawn.LoadSynchronous(),
		   GetActorTransform(),
		   nullptr,
		   nullptr,
		   ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	   );
	
		if (IsValid(AI))
		{
			UGameplayStatics::FinishSpawningActor(AI, GetActorTransform());
			if (IsValid(Spline))
			{
				TArray<AActor*> Checkpoints;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARTDRaceCheckpoint::StaticClass(), Checkpoints);
				AI->SetTrackParameters(Spline->Spline, Checkpoints);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Spline is invalid for AI initialization!"));
			}
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Failed to spawn AI actor instance!"));
}
