// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RTDAISpline.h"

#include "LandscapeSplinesComponent.h"
#include "LandscapeSplineSegment.h"

// Sets default values
ARTDAISpline::ARTDAISpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARTDAISpline::BeginPlay()
{
	Super::BeginPlay();
}

void ARTDAISpline::OnConstruction(const FTransform& Transform)
{
	AutoGenerateSplineFromLandscape();	
}

// Called every frame
void ARTDAISpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTDAISpline::AutoGenerateSplineFromLandscape()
{
	if (!IsValid(LandscapeSplineActor)) return;
	if (ULandscapeSplinesComponent* LandscapeSpline = LandscapeSplineActor->GetSplinesComponent())
	{
		if (IsValid(LandscapeSpline))
		{
			Spline->ClearSplinePoints(false);

			for (const ULandscapeSplineSegment* Segment : LandscapeSpline->GetSegments())
			{
				for (const FLandscapeSplineInterpPoint& Point : Segment->GetPoints())
				{
					Spline->AddSplinePoint(Point.Center, ESplineCoordinateSpace::World, false);
				}
			}

			Spline->UpdateSpline();
		}
	}
}

