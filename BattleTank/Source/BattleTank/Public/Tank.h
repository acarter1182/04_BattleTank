// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class UTankBarrel; /// FORWARD DECLARATION, allows for REFERENCE ONLY HERE and makes dependencies very explicit without creating a chain of dependencies
/// if the need for calling functions then do #include instead

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup) /// NO SEMICOLON ON END OF UFUNCTIONS, BlueprintCallable allows the function to be called via blueprint OBVIOUS
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr; /// used here because it will have a UPROPERTY so can't be private, and nobody outside of Tank needs it so we dont make public

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // TODO find a sensible speed
	
};
