// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTDRaceCheckpoint.h"

#include "Lib/CheckpointInteractor.h"

// Sets default values
ARTDRaceCheckpoint::ARTDRaceCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Overlap = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap"));
	SetRootComponent(Root);
	Overlap->SetupAttachment(GetRootComponent());
	Overlap->SetBoxExtent(FVector(100.f, 100.f, 100.f)); //Test size.
}

// Called when the game starts or when spawned
void ARTDRaceCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	Overlap->OnComponentBeginOverlap.AddDynamic(this,&ARTDRaceCheckpoint::OnCheckpointOverlap);
}

void ARTDRaceCheckpoint::OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UCheckpointInteractor::StaticClass()))
	{
		ICheckpointInteractor::Execute_OnCheckpointReached(OtherActor,this);
		SetActorHiddenInGame(true);
		if (IsValid(NextCheckpoint))
		{
			NextCheckpoint->SetActorHiddenInGame(false);
		}
	}
}

// Called every frame
void ARTDRaceCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

