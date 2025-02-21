// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/FRTDCarCustomizationParams.h"
#include "RacingTechDemoGameInstance.generated.h"

//This is just a practice that I like to use that setting major properties will broadcast an event if bound.
//I also like to pass the object that broadcasts the event as a param just in case another object needs to reference it.
//In this case we could always just cast back to the game instance, but this is helpful for things like multiplayer.
//For example, if a player's health updates, and they are in your party, you might want a reference to the player to gather their health stats without doing any sort of reverse lookups.
//You can also, obviously, just pass through the values that change, but this gives more flexibility and will make it easier to scale the codebase if you need to check more properties when an event happens.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomizationParamsUpdated, URacingTechDemoGameInstance*, Instance);

/**
 * 
 */
UCLASS()
class RACINGTECHDEMO_API URacingTechDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable,Category = "Customization")
	FOnCustomizationParamsUpdated OnCustomizationParamsUpdated;
	
	/**
	 * Set the new params.
	 * @param InParams - The new car customization params.
	 */
	UFUNCTION(BlueprintCallable,Category = "Customization")
	void SetCarCustomizationParams(const FRTDCarCustomizationParams& InParams);

	/**
	 * Return the value.
	 * @return - CarCustomizationParams.
	 */
	UFUNCTION(BlueprintPure,BlueprintNativeEvent,Category = "Customization")
	FRTDCarCustomizationParams GetCarCustomizationParams() const;

private:

	UPROPERTY()
	FRTDCarCustomizationParams CarCustomizationParams;
	
};
