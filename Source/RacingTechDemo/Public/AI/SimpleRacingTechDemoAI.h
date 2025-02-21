// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Vehicle/RacingTechDemoSportsCar.h"
#include "SimpleRacingTechDemoAI.generated.h"

/**
 * 
 */
UCLASS()
class RACINGTECHDEMO_API ASimpleRacingTechDemoAI : public ARacingTechDemoSportsCar
{
	GENERATED_BODY()

public:
	ASimpleRacingTechDemoAI ();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly, Category = "AI")
	void SetTrackParameters(USplineComponent* InSpline, TArray<AActor*> InCheckpoints);

protected:
	virtual void BeginPlay() override;

private:
	void FollowSpline(float DeltaTime);
	void MakeMistake(float DeltaTime);
	void RecoverFromMistake(float DeltaTime);

	UPROPERTY()
	USplineComponent* TrackSpline;

	UPROPERTY(EditAnywhere, Category = "AI")
	float SteeringErrorChance = 0.05f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxSteeringError = 0.3f;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<AActor*> Checkpoints;
	int32 CurrentCheckpointIndex;

	bool bIsMakingMistake;
	float MistakeDuration;
};
