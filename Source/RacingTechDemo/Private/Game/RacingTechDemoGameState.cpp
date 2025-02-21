// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RacingTechDemoGameState.h"

#include "Net/UnrealNetwork.h"

void ARacingTechDemoGameState::Server_ReportCheckpoint_Implementation(AActor* CheckpointHit, ARTDRaceCheckpoint* Checkpoint)
{
	if (!IsValid(CheckpointHit) || !IsValid(Checkpoint)) return; 
	int32 TestIndex;
	FRTDCheckpointProgress TestValue;
	if (!GetCheckpointProgressForActor(CheckpointHit,TestIndex,TestValue))
	{
		TArray<float> TimeToCheckpoint;
		TimeToCheckpoint.Add(GetServerWorldTimeSeconds());
		CheckpointProgress.Add(FRTDCheckpointProgress(CheckpointHit->GetFName(),CheckpointHit,Checkpoint,TimeToCheckpoint,0));
	}
	else
	{
		TestValue.LastCheckpoint = Checkpoint;
		TestValue.TimeToCheckpoint.Add(GetServerWorldTimeSeconds());
		if (Checkpoint->bIsLapCounter)
		{
			TestValue.CurrentLaps++;
		}
		CheckpointProgress[TestIndex] = TestValue; //Avoids multiple rep notifies.
	}
	if (OnReportCheckpoint.IsBound())
	{
		OnReportCheckpoint.Broadcast(this);
	}
}

TArray<FRTDCheckpointProgress> ARacingTechDemoGameState::GetCheckpointProgress() const
{
	return CheckpointProgress;
}

bool ARacingTechDemoGameState::GetCheckpointProgressForActor(AActor* Actor,int32& Index, FRTDCheckpointProgress& Value) const
{
	const TArray<FRTDCheckpointProgress>& Progress = GetCheckpointProgress();
	for (const auto& Temp : Progress)
	{
		if (Temp.CurrentActor == Actor)
		{
			Value = Temp;
			Index = Progress.Find(Temp);
			return true;
		}
	}
	return false;
}

void ARacingTechDemoGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ARacingTechDemoGameState, CheckpointProgress, COND_None, REPNOTIFY_OnChanged);
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ARacingTechDemoGameState::OnRep_CheckpointProgress()
{
	if (OnReportCheckpoint.IsBound())
	{
		OnReportCheckpoint.Broadcast(this);
	}	
}