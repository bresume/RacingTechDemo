// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "RTDRaceCheckpoint.generated.h"

UCLASS()
class RACINGTECHDEMO_API ARTDRaceCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTDRaceCheckpoint();

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "Components")
	UBoxComponent* Overlap;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Checkpoint")
	ARTDRaceCheckpoint* LastCheckpoint;
			
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Checkpoint")
	ARTDRaceCheckpoint* NextCheckpoint;
			
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Checkpoint")
	bool bIsLapCounter;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
