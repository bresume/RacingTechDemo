// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle/RacingTechDemoWheelFront.h"
#include "UObject/ConstructorHelpers.h"

URacingTechDemoWheelFront::URacingTechDemoWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}