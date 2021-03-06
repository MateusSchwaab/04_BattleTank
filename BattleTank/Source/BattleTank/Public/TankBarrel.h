// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//-1 is max down movement and +1 max upward
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecound = 5; //sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0;

};
