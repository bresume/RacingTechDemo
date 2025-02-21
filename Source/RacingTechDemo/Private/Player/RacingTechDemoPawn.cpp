// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RacingTechDemoPawn.h"
#include "Vehicle/RacingTechDemoWheelFront.h"
#include "Vehicle/RacingTechDemoWheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EngineUtils.h"
#include "Game/RacingTechDemoGameInstance.h"
#include "Game/RacingTechDemoGameState.h"
#include "Game/RTDRaceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

DEFINE_LOG_CATEGORY(LogTemplateVehicle);

ARacingTechDemoPawn::ARacingTechDemoPawn()
{
	// construct the front camera boom
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = false;

	// construct the back camera boom
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bEnableCameraRotationLag = true;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Configure the car mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	// get the Chaos Wheeled movement component
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

}

void ARacingTechDemoPawn::BeginPlay()
{
	Super::BeginPlay();
	//TODO::Replace with a subsystem or something.
	if (ARTDRaceManager* RaceManager = Cast<ARTDRaceManager>(UGameplayStatics::GetActorOfClass(this,ARTDRaceManager::StaticClass())))
	{
		RaceManager->OnRaceCountdownFinished.AddDynamic(this, &ARacingTechDemoPawn::OnRaceCountdownFinished);
		return;
	}
	bInputEnabled = true;//Enable input when in the customization menu.
}

void ARacingTechDemoPawn::OnRaceCountdownFinished(ARTDRaceManager* RaceManager)
{
	bInputEnabled = true; //Disable race countdown until input is allowed. Kinda hacky, but it should work for a day!
}

void ARacingTechDemoPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ARacingTechDemoPawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ARacingTechDemoPawn::Throttle);

		// break 
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &ARacingTechDemoPawn::StartBrake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ARacingTechDemoPawn::StopBrake);

		// handbrake 
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &ARacingTechDemoPawn::StartHandbrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ARacingTechDemoPawn::StopHandbrake);

		// look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::LookAround);

		// toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::ToggleCamera);

		// reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &ARacingTechDemoPawn::ResetVehicle);
	}
}

void ARacingTechDemoPawn::OnCheckpointReached_Implementation(ARTDRaceCheckpoint* Checkpoint)
{
	if (ARacingTechDemoGameState* GS = GetWorld()->GetGameState<ARacingTechDemoGameState>())
	{
		int32 TestIndex;
		FRTDCheckpointProgress TestValue;
		if (GS->GetCheckpointProgressForActor(this,TestIndex,TestValue))
		{
			if (TestValue.LastCheckpoint == Checkpoint->LastCheckpoint)
			{
				GS->Server_ReportCheckpoint_Implementation(this, Checkpoint); //You have to hit the last checkpoint before hitting the next one. 
			}
		}
	}
}

void ARacingTechDemoPawn::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ARacingTechDemoPawn, CarCustomizationParams, COND_None, REPNOTIFY_OnChanged);
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ARacingTechDemoPawn::Tick(float Delta)
{
	Super::Tick(Delta);
	// add some angular damping if the vehicle is in midair
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);

	// realign the camera yaw to face front
	float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, Delta, 1.0f);

	BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
}

void ARacingTechDemoPawn::Steering(const FInputActionValue& Value)
{
	// get the input magnitude for steering
	float SteeringValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void ARacingTechDemoPawn::Throttle(const FInputActionValue& Value)
{
	if (!bInputEnabled) return;
	// get the input magnitude for the throttle
	float ThrottleValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void ARacingTechDemoPawn::Brake(const FInputActionValue& Value)
{
	// get the input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void ARacingTechDemoPawn::StartBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ARacingTechDemoPawn::StopBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(false);

	// reset brake input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void ARacingTechDemoPawn::StartHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(true);

	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ARacingTechDemoPawn::StopHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(false);

	// call the Blueprint hook for the break lights
	BrakeLights(false);
}

void ARacingTechDemoPawn::LookAround(const FInputActionValue& Value)
{
	// get the flat angle value for the input 
	float LookValue = Value.Get<float>();

	// add the input
	BackSpringArm->AddLocalRotation(FRotator(0.0f, LookValue, 0.0f));
}

void ARacingTechDemoPawn::ToggleCamera(const FInputActionValue& Value)
{
	// toggle the active camera flag
	bFrontCameraActive = !bFrontCameraActive;

	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void ARacingTechDemoPawn::ResetVehicle(const FInputActionValue& Value)
{
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;
	
	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemplateVehicle, Error, TEXT("Reset Vehicle"));
}

void ARacingTechDemoPawn::GetCustomizationParams_Implementation()
{
	if (URacingTechDemoGameInstance* GI = GetWorld()->GetGameInstance<URacingTechDemoGameInstance>())
	{
		SetCustomizationParams(GI->GetCarCustomizationParams());
	}
}

void ARacingTechDemoPawn::SetCustomizationParams_Implementation(const FRTDCarCustomizationParams& Customization)
{
	CarCustomizationParams = Customization;
	ApplyCarCustomizationParams();
}

void ARacingTechDemoPawn::ApplyCarCustomizationParams()
{
	if (IsValid(GetChaosVehicleMovement()))
	{
		//GetChaosVehicleMovement()->EngineSetup = CarCustomizationParams.Engine.ToEngineConfig();
		//GetChaosVehicleMovement()->DifferentialSetup = CarCustomizationParams.Differential.ToDifferentialConfig();
		//GetChaosVehicleMovement()->TransmissionSetup = CarCustomizationParams.Transmission.ToTransmissionConfig();
		//GetChaosVehicleMovement()->SteeringSetup = CarCustomizationParams.Steering.ToSteeringConfig();
		//TODO::More customization like drag and wheels and stuff.
		//The code above was causing a crash.
		GetChaosVehicleMovement()->EngineSetup.MaxTorque = CarCustomizationParams.Engine.MaxTorque;
		GetChaosVehicleMovement()->EngineSetup.MaxRPM = CarCustomizationParams.Engine.MaxRPM;
		GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = CarCustomizationParams.Engine.EngineIdleRPM;
		GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = CarCustomizationParams.Engine.EngineBrakeEffect;
		GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = CarCustomizationParams.Engine.EngineRevUpMOI;
		GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = CarCustomizationParams.Engine.EngineRevDownRate;

		// Set up the transmission
		GetChaosVehicleMovement()->TransmissionSetup.bUseAutomaticGears = CarCustomizationParams.Transmission.bUseAutomaticGears;
		GetChaosVehicleMovement()->TransmissionSetup.bUseAutoReverse = CarCustomizationParams.Transmission.bUseAutoReverse;
		GetChaosVehicleMovement()->TransmissionSetup.FinalRatio = CarCustomizationParams.Transmission.FinalRatio;
		GetChaosVehicleMovement()->TransmissionSetup.ChangeUpRPM = CarCustomizationParams.Transmission.ChangeUpRPM;
		GetChaosVehicleMovement()->TransmissionSetup.ChangeDownRPM = CarCustomizationParams.Transmission.ChangeDownRPM;
		GetChaosVehicleMovement()->TransmissionSetup.GearChangeTime = CarCustomizationParams.Transmission.GearChangeTime;
		GetChaosVehicleMovement()->TransmissionSetup.TransmissionEfficiency = CarCustomizationParams.Transmission.TransmissionEfficiency;

		GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios.SetNum(CarCustomizationParams.Transmission.ForwardGearRatios.Num());
		GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios = CarCustomizationParams.Transmission.ForwardGearRatios;

		GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios.SetNum(CarCustomizationParams.Transmission.ReverseGearRatios.Num());
		GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios = CarCustomizationParams.Transmission.ReverseGearRatios;
		
		// Set up the steering
		// NOTE: Check the Blueprint asset for the Steering Curve
		GetChaosVehicleMovement()->SteeringSetup.SteeringType = CarCustomizationParams.Steering.SteeringType;
		GetChaosVehicleMovement()->SteeringSetup.AngleRatio = CarCustomizationParams.Steering.AngleRatio;
	}
}

void ARacingTechDemoPawn::OnRep_CarCustomizationParams()
{
	ApplyCarCustomizationParams();
}

#undef LOCTEXT_NAMESPACE