// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RacingTechDemoGameMode.h"
#include "Player/RacingTechDemoPlayerController.h"

ARacingTechDemoGameMode::ARacingTechDemoGameMode()
{
	PlayerControllerClass = ARacingTechDemoPlayerController::StaticClass();
}
