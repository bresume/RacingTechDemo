// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/DataTable.h"
#include "FRTDEngineSetup.generated.h"

/**
 * Wrapper for the standard chaos engine setup since it's not a BlueprintType.
 */
USTRUCT(BlueprintType)
struct RACINGTECHDEMO_API FRTDEngineSetup : public FTableRowBase
{
	
	GENERATED_BODY()
	
public:
	
	FRTDEngineSetup()
	{
		InitDefaults();
	}

	FORCEINLINE bool operator == (const FRTDEngineSetup& Other) const
	{
		return MaxTorque == Other.MaxTorque && MaxRPM == Other.MaxRPM && EngineIdleRPM == Other.EngineIdleRPM && EngineBrakeEffect == Other.EngineBrakeEffect && EngineRevUpMOI == Other.EngineRevUpMOI && EngineRevDownRate == Other.EngineRevDownRate;
	}

	FVehicleEngineConfig ToEngineConfig() const //Unfortunately directly casting caused a crash, but it was going to be a cool flex =/
	{
		FVehicleEngineConfig Config;
		Config.MaxTorque = MaxTorque;
		Config.MaxRPM = MaxRPM;
		Config.EngineIdleRPM = EngineIdleRPM;
		Config.EngineBrakeEffect = EngineBrakeEffect;
		Config.EngineRevUpMOI = EngineRevUpMOI;
		Config.EngineRevDownRate = EngineRevDownRate;
		Config.TorqueCurve = TorqueCurve;
		return Config;
	}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	/** Torque [Normalized 0..1] for a given RPM */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRuntimeFloatCurve TorqueCurve;

	/** Max Engine Torque (Nm) is multiplied by TorqueCurve */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxTorque;

	/** Maximum revolutions per minute of the engine */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MaxRPM;

	/** Idle RMP of engine then in neutral/stationary */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float EngineIdleRPM;

	/** Braking effect from engine, when throttle released */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EngineBrakeEffect;

	/** Affects how fast the engine RPM speed up */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float EngineRevUpMOI;

	/** Affects how fast the engine RPM slows down */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float EngineRevDownRate;

	void InitDefaults()
	{
		MaxTorque = 300.0f;
		MaxRPM = 4500.0f;
		EngineIdleRPM = 1200.0f;
		EngineBrakeEffect = 0.05f;
		EngineRevUpMOI = 5.0f;
		EngineRevDownRate = 600.0f;
	}

};
