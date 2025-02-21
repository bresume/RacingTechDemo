// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RacingTechDemoGameInstance.h"

void URacingTechDemoGameInstance::SetCarCustomizationParams(const FRTDCarCustomizationParams& InParams)
{
	CarCustomizationParams = InParams;
	if (OnCustomizationParamsUpdated.IsBound())
	{
		OnCustomizationParamsUpdated.Broadcast(this);
	}
}

FRTDCarCustomizationParams URacingTechDemoGameInstance::GetCarCustomizationParams_Implementation() const
{
	return CarCustomizationParams;
}