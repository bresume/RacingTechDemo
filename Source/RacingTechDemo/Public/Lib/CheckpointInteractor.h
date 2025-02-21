// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RTDRaceCheckpoint.h"
#include "UObject/Interface.h"
#include "CheckpointInteractor.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCheckpointInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RACINGTECHDEMO_API ICheckpointInteractor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Checkpoints")
	void OnCheckpointReached(ARTDRaceCheckpoint* Checkpoint);
	
};
