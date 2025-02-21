// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/DataTable.h"
#include "FRTDSteeringConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDSteeringConfig : public FTableRowBase
{

	GENERATED_BODY()
	
public:
	FRTDSteeringConfig()
	{
		InitDefaults();
	}

	void InitDefaults()
	{
		SteeringType = ESteeringType::AngleRatio;
		AngleRatio = 0.7f;

		// Init steering speed curve
		FRichCurve* SteeringCurveData = SteeringCurve.GetRichCurve();
		SteeringCurveData->AddKey(0.f, 1.f);
		SteeringCurveData->AddKey(20.f, 0.8f);
		SteeringCurveData->AddKey(60.f, 0.4f);
		SteeringCurveData->AddKey(120.f, 0.3f);
	}

	FVehicleSteeringConfig ToSteeringConfig() const
	{
		FVehicleSteeringConfig Config;
		Config.SteeringType = SteeringType;
		Config.SteeringCurve = SteeringCurve;
		Config.AngleRatio = AngleRatio;
		return Config;
	}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	/** Single angle : both wheels steer by the same amount
	 *  AngleRatio   : outer wheels on corner steer less than the inner ones by set ratio 
	 *  Ackermann	 : Ackermann steering principle is applied */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESteeringType SteeringType;

	/** Only applies when AngleRatio is selected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AngleRatio; 

	/** Maximum steering versus forward speed (MPH) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRuntimeFloatCurve SteeringCurve;

};
