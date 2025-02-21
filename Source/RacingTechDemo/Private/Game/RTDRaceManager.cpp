// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTDRaceManager.h"

#include "Game/RacingTechDemoGameState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ARTDRaceManager::ARTDRaceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	RaceCountdown = 0;
}

// Called when the game starts or when spawned
void ARTDRaceManager::BeginPlay()
{
	Super::BeginPlay();
	if (UKismetSystemLibrary::IsServer(this))
	{
		if (ARacingTechDemoGameState* GS = GetWorld()->GetGameState<ARacingTechDemoGameState>())
		{
			GS->OnReportCheckpoint.AddDynamic(this,&ARTDRaceManager::HandleCheckpoints);
		}
		RaceCountdown = CountdownStartTime;
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle,this,&ARTDRaceManager::StartRaceCountdownTick,3.f,false);
	}
}

void ARTDRaceManager::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ARTDRaceManager, FinishedRacers, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(ARTDRaceManager, RaceCountdown, COND_None, REPNOTIFY_OnChanged);
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ARTDRaceManager::HandleCheckpoints(ARacingTechDemoGameState* GameState)
{
	if (!IsValid(GameState)) return;
	const TArray<FRTDCheckpointProgress> CheckpointProgress = GameState->GetCheckpointProgress();
	for (const auto& Checkpoint : CheckpointProgress)
	{
		if (!FinishedRacers.Contains(Checkpoint.CurrentActor) && Checkpoint.CurrentLaps >= LapsToWin)
		{
			FinishedRacers.AddUnique(Checkpoint.CurrentActor);
			GameState->NotifyRacerWon(Checkpoint.CurrentActor);
		}
	}
}

// Called every frame
void ARTDRaceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> ARTDRaceManager::GetFinishedRacers() const
{
	return FinishedRacers;
}

int32 ARTDRaceManager::GetRaceCountdown() const
{
	return RaceCountdown;
}

void ARTDRaceManager::RaceCountdownTick()
{
	RaceCountdown -= 1;
	if (RaceCountdown <= 0 && OnRaceCountdownFinished.IsBound())
	{
		OnRaceCountdownFinished.Broadcast(this);
		return; //You could also set the tick interval to 1, but I might use tick later.
	}
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,this,&ARTDRaceManager::RaceCountdownTick,1.f,false);
}

void ARTDRaceManager::StartRaceCountdownTick()
{
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,this,&ARTDRaceManager::RaceCountdownTick,1.f,false);
}

void ARTDRaceManager::OnRep_RaceCountdown()
{
	if (RaceCountdown <= 0 && OnRaceCountdownFinished.IsBound())
	{
		OnRaceCountdownFinished.Broadcast(this);
	}
}

