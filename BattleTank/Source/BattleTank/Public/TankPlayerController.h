// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:

	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	//start moving the barrel so the shot will hit the crosshair
	//the crosshair intersects the world
	void AimTowardsCrosshair();
	
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY (EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

};
