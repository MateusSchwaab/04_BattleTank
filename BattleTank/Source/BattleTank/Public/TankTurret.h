// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	//-1 is max down movement and +1 max upward
	void RotateTurret(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecound = 5; //sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotationDegrees = 90;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinRotationDegrees = -90;
	
};
