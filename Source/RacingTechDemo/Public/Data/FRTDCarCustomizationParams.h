// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRTDDifferentialConfig.h"
#include "FRTDSteeringConfig.h"
#include "FRTDTransmissionConfig.h"
#include "Data/FRTDEngineSetup.h"
#include "Engine/DataTable.h"
#include "FRTDCarCustomizationParams.generated.h"

/**
 * Customization params set by the player and passed to the car.
 * TODO::Wheel meshes/setup, drag coefficients, spoilers, decals, etc...
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDCarCustomizationParams : public FTableRowBase
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRTDEngineSetup Engine;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRTDDifferentialConfig Differential;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRTDTransmissionConfig Transmission;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRTDSteeringConfig Steering;

	FRTDCarCustomizationParams()
	{
		Name = NAME_None;
		Engine = FRTDEngineSetup();
		Differential = FRTDDifferentialConfig();
		Transmission = FRTDTransmissionConfig();
		Steering = FRTDSteeringConfig();
	}

	FRTDCarCustomizationParams(const FName& InName, const FRTDEngineSetup& InEngine, const FRTDDifferentialConfig& InDifferential,
		const FRTDTransmissionConfig& InTransmission, const FRTDSteeringConfig& InSteering)
	{
		Name = InName;
		Engine = InEngine;
		Differential = InDifferential;
		Transmission = InTransmission;
		Steering = InSteering;
	}
	
};
