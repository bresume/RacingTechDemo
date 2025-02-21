// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SimpleRacingTechDemoAI.h"
#include "Components/SplineComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

ASimpleRacingTechDemoAI::ASimpleRacingTechDemoAI()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsMakingMistake = false;
    MistakeDuration = 0.0f;
    CurrentCheckpointIndex = 0;
    TrackSpline = nullptr;
}

void ASimpleRacingTechDemoAI::BeginPlay()
{
    Super::BeginPlay();
}

void ASimpleRacingTechDemoAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!bInputEnabled) return;
    if (bIsMakingMistake)
    {
        MakeMistake(DeltaTime);
    }
    else
    {
        FollowSpline(DeltaTime);

        if (FMath::FRand() < SteeringErrorChance)
        {
            bIsMakingMistake = true;
            MistakeDuration = FMath::RandRange(1.0f, 3.0f); 
        }
    }
}

void ASimpleRacingTechDemoAI::SetTrackParameters(USplineComponent* InSpline, TArray<AActor*> InCheckpoints)
{
    TrackSpline = InSpline;
    Checkpoints = InCheckpoints;
}

void ASimpleRacingTechDemoAI::FollowSpline(float DeltaTime)
{
    if (!IsValid(TrackSpline)) return;

    FVector CurrentLocation = GetActorLocation();
    float Distance = TrackSpline->FindInputKeyClosestToWorldLocation(CurrentLocation);
    FVector TargetLocation = TrackSpline->GetLocationAtSplineInputKey(Distance + 1.0f, ESplineCoordinateSpace::World);
    FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
    FRotator TargetRotation = Direction.Rotation();
    float SteeringAngle = FMath::Clamp(FMath::FindDeltaAngleDegrees(GetActorRotation().Yaw, TargetRotation.Yaw), -1.0f, 1.0f);
    GetVehicleMovementComponent()->SetSteeringInput(SteeringAngle);
    GetVehicleMovementComponent()->SetThrottleInput(1.0f);
}

void ASimpleRacingTechDemoAI::MakeMistake(float DeltaTime)
{
    MistakeDuration -= DeltaTime;

    float ErrorAmount = FMath::FRandRange(-MaxSteeringError, MaxSteeringError);
    GetVehicleMovementComponent()->SetSteeringInput(ErrorAmount);

    if (MistakeDuration <= 0.0f)
    {
        bIsMakingMistake = false;
    }
}

void ASimpleRacingTechDemoAI::RecoverFromMistake(float DeltaTime)
{
    FollowSpline(DeltaTime);
}
