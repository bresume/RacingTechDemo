// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/DataTable.h"
#include "FRTDDifferentialConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDDifferentialConfig : public FTableRowBase
{

	GENERATED_BODY()
	
public:

	FRTDDifferentialConfig()
	{
		InitDefaults();
	}

	void InitDefaults()
	{
		DifferentialType = EVehicleDifferential::RearWheelDrive;
		FrontRearSplit = 0.5f;
	}

	FVehicleDifferentialConfig ToDifferentialConfig() const
	{
		FVehicleDifferentialConfig Config;
		Config.DifferentialType = DifferentialType;
		Config.FrontRearSplit = FrontRearSplit;
		return Config;
	}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	/** Type of differential */
	UPROPERTY(EditAnywhere, Category=Setup)
	EVehicleDifferential DifferentialType;
	
	/** Ratio of torque split between front and rear (<0.5 means more to front, >0.5 means more to rear, works only with 4W type) */
	UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float FrontRearSplit;

};
