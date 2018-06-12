// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecound * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation , 0.f, 0.f));
}


