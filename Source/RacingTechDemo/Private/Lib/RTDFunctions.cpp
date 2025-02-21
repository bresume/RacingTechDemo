// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib/RTDFunctions.h"

FRTDCarCustomizationParams URTDFunctions::UpdateEngineConfig(const FRTDCarCustomizationParams& InParams, const FRTDEngineSetup& InEngineSetup)
{
	FRTDCarCustomizationParams OutParams = InParams;
	OutParams.Engine = InEngineSetup;
	return OutParams;
}
	
FRTDCarCustomizationParams URTDFunctions::UpdateSteeringConfig(const FRTDCarCustomizationParams& InParams, const FRTDSteeringConfig& InSteeringSetup)
{
	FRTDCarCustomizationParams OutParams = InParams;
	OutParams.Steering = InSteeringSetup;
	return OutParams;
}
	
FRTDCarCustomizationParams URTDFunctions::UpdateTransmissionConfig(const FRTDCarCustomizationParams& InParams, const FRTDTransmissionConfig& InTransmissionSetup)
{
	FRTDCarCustomizationParams OutParams = InParams;
	OutParams.Transmission = InTransmissionSetup;
	return OutParams;
}

FRTDCarCustomizationParams URTDFunctions::UpdateDifferentialConfig(const FRTDCarCustomizationParams& InParams, const FRTDDifferentialConfig& InDifferentialSetup)
{
	FRTDCarCustomizationParams OutParams = InParams;
	OutParams.Differential = InDifferentialSetup;
	return OutParams;
}
	