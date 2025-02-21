// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandscapeSplineActor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "RTDAISpline.generated.h"

UCLASS()
class RACINGTECHDEMO_API ARTDAISpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTDAISpline();

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	ALandscapeSplineActor* LandscapeSplineActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void AutoGenerateSplineFromLandscape();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
