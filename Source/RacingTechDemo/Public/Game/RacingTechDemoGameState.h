// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RacingTechDemoGameMode.h"
#include "RTDRaceCheckpoint.h"
#include "Data/FRTDCheckpointProgress.h"
#include "GameFramework/GameStateBase.h"
#include "RacingTechDemoGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReportCheckpoint,ARacingTechDemoGameState*, GameState);

/**
 * 
 */
UCLASS()
class RACINGTECHDEMO_API ARacingTechDemoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable,Category = "Game")
	FReportCheckpoint OnReportCheckpoint;
	
	//Skipping validation here since this is just a tech demo and I have limited time,
	//but some sort of validation should be implemented IE checking car and checkpoint location to make sure they match a threshold.
	UFUNCTION(Server,Reliable,Category = "Game") 
	void Server_ReportCheckpoint(AActor* CheckpointHit, ARTDRaceCheckpoint* Checkpoint);

	UFUNCTION(BlueprintPure,Category = "Game")
	TArray<FRTDCheckpointProgress> GetCheckpointProgress() const;

	UFUNCTION(BlueprintPure,Category = "Game")
	bool GetCheckpointProgressForActor(AActor* Actor,int32& Index, FRTDCheckpointProgress& Value) const;

	UFUNCTION(BlueprintImplementableEvent,Category = "Game")
	void NotifyRacerWon(AActor* Racer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void OnRep_CheckpointProgress();

	UPROPERTY(ReplicatedUsing = "OnRep_CheckpointProgress")
	TArray<FRTDCheckpointProgress> CheckpointProgress;
	
};
