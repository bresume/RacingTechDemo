// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/DataTable.h"
#include "FRTDTransmissionConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDTransmissionConfig : public FTableRowBase
{

	GENERATED_BODY()
	
public:
	FRTDTransmissionConfig()
	{
		InitDefaults();
	}

	FVehicleTransmissionConfig ToTransmissionConfig() const
	{
		FVehicleTransmissionConfig Config;
		Config.bUseAutomaticGears = bUseAutomaticGears;
		Config.bUseAutoReverse = bUseAutoReverse;
		Config.FinalRatio = FinalRatio;
		Config.ForwardGearRatios = ForwardGearRatios;
		Config.ReverseGearRatios = ReverseGearRatios;
		Config.ChangeUpRPM = ChangeUpRPM;
		Config.ChangeDownRPM = ChangeDownRPM;
		Config.GearChangeTime = GearChangeTime;
		Config.TransmissionEfficiency = TransmissionEfficiency;
		return Config;
	}

	void InitDefaults()
	{
		bUseAutomaticGears = true;
		bUseAutoReverse = true;
		FinalRatio = 3.08f;

		ForwardGearRatios.Add(2.85f);
		ForwardGearRatios.Add(2.02f);
		ForwardGearRatios.Add(1.35f);
		ForwardGearRatios.Add(1.0f);

		ReverseGearRatios.Add(2.86f);

		ChangeUpRPM = 4500.0f;
		ChangeDownRPM = 2000.0f;
		GearChangeTime = 0.4f;

		TransmissionEfficiency = 0.9f;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	/** Whether to use automatic transmission */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName = "Automatic Transmission"))
	bool bUseAutomaticGears;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Automatic Reverse"))
	bool bUseAutoReverse;

	/** The final gear ratio multiplies the transmission gear ratios.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay)
	float FinalRatio;

	/** Forward gear ratios */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay)
	TArray<float> ForwardGearRatios;

	/** Reverse gear ratio(s) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay)
	TArray<float> ReverseGearRatios;

	/** Engine Revs at which gear up change ocurrs */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "50000.0", UIMax = "50000.0"))
	float ChangeUpRPM;

	/** Engine Revs at which gear down change ocurrs */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "50000.0", UIMax = "50000.0"))
	float ChangeDownRPM;

	/** Time it takes to switch gears (seconds) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float GearChangeTime;

	/** Mechanical frictional losses mean transmission might operate at 0.94 (94% efficiency) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay)
	float TransmissionEfficiency;

};
