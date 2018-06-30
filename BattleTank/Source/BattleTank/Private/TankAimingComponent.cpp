// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include  "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//So that first fire is after three seconds
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto ForwardVector = Barrel->GetForwardVector();
	if (bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecounds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();
	if (!AimDirection.Equals(ForwardVector, 0.1))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}

void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));





	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, OutHitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	

		FRotator AimAsRotator = AimDirection.Rotation();
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator DeltaRotator = AimAsRotator - BarrelRotator;


		Barrel->ElevateBarrel(DeltaRotator.Pitch);
		Turret->RotateTurret(DeltaRotator.Yaw);
	
}

void UTankAimingComponent::Fire()
{

	if (FiringState != EFiringState::Reloading)
	{


		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
