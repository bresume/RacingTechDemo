// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FRTDCarCustomizationParams.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTDFunctions.generated.h"

/**
 * 
 */
UCLASS()
class RACINGTECHDEMO_API URTDFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure,Category = "Customization")
	static FRTDCarCustomizationParams UpdateEngineConfig(const FRTDCarCustomizationParams& InParams, const FRTDEngineSetup& InEngineSetup);
	
	UFUNCTION(BlueprintPure,Category = "Customization")
	static FRTDCarCustomizationParams UpdateSteeringConfig(const FRTDCarCustomizationParams& InParams, const FRTDSteeringConfig& InSteeringSetup);
		
	UFUNCTION(BlueprintPure,Category = "Customization")
	static FRTDCarCustomizationParams UpdateTransmissionConfig(const FRTDCarCustomizationParams& InParams, const FRTDTransmissionConfig& InTransmissionSetup);
		
	UFUNCTION(BlueprintPure,Category = "Customization")
	static FRTDCarCustomizationParams UpdateDifferentialConfig(const FRTDCarCustomizationParams& InParams, const FRTDDifferentialConfig& InDifferentialSetup);
	
};
