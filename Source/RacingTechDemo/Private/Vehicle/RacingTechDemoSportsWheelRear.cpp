// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/RacingTechDemoSportsWheelRear.h"

URacingTechDemoSportsWheelRear::URacingTechDemoSportsWheelRear()
{
	WheelRadius = 40.f;
	WheelWidth = 40.0f;
	FrictionForceMultiplier = 4.0f;
	SlipThreshold = 100.0f;
	SkidThreshold = 100.0f;
	MaxSteerAngle = 0.0f;
	MaxHandBrakeTorque = 6000.0f;
}