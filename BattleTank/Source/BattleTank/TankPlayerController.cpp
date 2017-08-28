// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h" /// might not be needed


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); /// makes sure the BeginPlay function is called on the PARENT class this inherits from

	auto ControlledTank = GetControlledTank(); /// auto keyword to automatically figure out the type

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); /// makes sure the Tick function is called on the PARENT class this inherits from
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Tick is working!"));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); /// to find out which tank we are controlling
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; } /// dont start aiming unless we have a controlled tank

	FVector HitLocation; // OUT PARAMETER
	if (GetSightRayHitLocation(HitLocation)) /// pass in HitLocation as the thing used as OUT PARAMETER, has "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());

		// TODO tell controlled tank to aim at this point
	}
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString()); /// remember to add the * to convert into TCHAR for to string
	// "De-project" the screen position of the crosshair to a world direction (screen coords to world coords?)
	// Line-trace along that look direction, and see what we hit (up to max range)
	//HitLocation = FVector(1.0f);
	return true;
}
