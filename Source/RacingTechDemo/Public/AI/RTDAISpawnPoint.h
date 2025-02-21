// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleRacingTechDemoAI.h"
#include "GameFramework/Actor.h"
#include "AI/RTDAISpline.h"
#include "RTDAISpawnPoint.generated.h"

UCLASS()
class RACINGTECHDEMO_API ARTDAISpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTDAISpawnPoint();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI")
	TSoftClassPtr<ASimpleRacingTechDemoAI> AIToSpawn = ASimpleRacingTechDemoAI::StaticClass();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	ARTDAISpline* Spline;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UFUNCTION()
	void SpawnAI();
	
};
