// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RacingTechDemoGameState.h"
#include "GameFramework/Actor.h"
#include "RTDRaceManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRaceCountdownFinished, ARTDRaceManager*, RaceManager);

/**
 * All of this can be done in the game state, but I put it here so there could be flexibility between maps.
 * TODO::Race countdown that disables player input until the timer finishes.
 */
UCLASS()
class RACINGTECHDEMO_API ARTDRaceManager : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable,Category = "Race")
	FRaceCountdownFinished OnRaceCountdownFinished;
	
	// Sets default values for this actor's properties
	ARTDRaceManager();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Race")
	int32 LapsToWin = 3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Race")
	int32 CountdownStartTime = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void HandleCheckpoints(ARacingTechDemoGameState* GameState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure,Category = "Game")
	TArray<AActor*> GetFinishedRacers() const;
	
	UFUNCTION(BlueprintPure,Category = "Game")
	int32 GetRaceCountdown() const;
	
private:

	UFUNCTION()
	void RaceCountdownTick();

	UFUNCTION()
	void StartRaceCountdownTick();

	UFUNCTION()
	void OnRep_RaceCountdown();
	
	UPROPERTY(Replicated)
	TArray<AActor*> FinishedRacers;

	UPROPERTY(ReplicatedUsing = "OnRep_RaceCountdown")
	int32 RaceCountdown;
	
};
