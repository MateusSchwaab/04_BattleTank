// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};



//forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//"Holds Barrel's properties"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Locked;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


	UFUNCTION(BlueprintCallable)
		void Fire();



	void AimAt(FVector OutHitLocation);

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UTankTurret * Turret = nullptr;
	UTankBarrel * Barrel = nullptr;

	

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecounds = 3;

	double LastFireTime = 0;
	
	void MoveBarrel(FVector AimDirection);


	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000; //sensible starting value

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

};
