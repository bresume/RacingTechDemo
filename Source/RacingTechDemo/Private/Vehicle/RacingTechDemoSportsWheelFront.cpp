// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/RacingTechDemoSportsWheelFront.h"

URacingTechDemoSportsWheelFront::URacingTechDemoSportsWheelFront()
{
	WheelRadius = 39.0f;
	WheelWidth = 35.0f;
	FrictionForceMultiplier = 3.0f;

	MaxBrakeTorque = 4500.0f;
	MaxHandBrakeTorque = 6000.0f;
}