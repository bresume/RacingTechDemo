// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Game/RTDRaceCheckpoint.h"
#include "FRTDCheckpointProgress.generated.h"

/**
 * This tracks checkpoint progress.
 * It doesn't need to be FTableRowBase or have the FName identifier property, but I like to do this will all of my structs just in case.
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDCheckpointProgress : public FTableRowBase
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* CurrentActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ARTDRaceCheckpoint* LastCheckpoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<float> TimeToCheckpoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CurrentLaps;

	FORCEINLINE bool operator==(const FRTDCheckpointProgress& Other) const //== operator so we can use find/remove and predicates if needed.
	{
		return Name == Other.Name && CurrentActor == Other.CurrentActor && LastCheckpoint == Other.LastCheckpoint;
	}
	
	FRTDCheckpointProgress()
	{
		Name = NAME_None;
		CurrentActor = nullptr;
		LastCheckpoint = nullptr;
		TimeToCheckpoint.Empty();
		CurrentLaps = 0;
	}

	FRTDCheckpointProgress(const FName& InName, AActor* InActor, ARTDRaceCheckpoint* InLastCheckpoint, const TArray<float>& InTimeToCheckpoint, int32 InCurrentLaps)
	{
		Name = InName;
		CurrentActor = InActor;
		LastCheckpoint = InLastCheckpoint;
		TimeToCheckpoint = InTimeToCheckpoint;
		CurrentLaps = InCurrentLaps;
	}
	
};
