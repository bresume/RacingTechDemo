// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/RacingTechDemoPawn.h"
#include "RacingTechDemoSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class RACINGTECHDEMO_API ARacingTechDemoSportsCar : public ARacingTechDemoPawn
{
	GENERATED_BODY()
	
public:

	ARacingTechDemoSportsCar();
};
