// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle/RacingTechDemoWheelRear.h"
#include "UObject/ConstructorHelpers.h"

URacingTechDemoWheelRear::URacingTechDemoWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}