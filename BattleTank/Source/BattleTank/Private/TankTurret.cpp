// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecound * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));
}






