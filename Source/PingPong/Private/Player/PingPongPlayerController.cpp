// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PingPongPlayerController.h"
#include "Player/PingPongPlayer.h"

// Allows the PlayerController to set up custom input bindings
void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind input functions
	InputComponent->BindAxis("MoveRight", this, &APingPongPlayerController::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &APingPongPlayerController::MoveForward);
}

// Call move right in pawn
void APingPongPlayerController::MoveRight(float Value)
{
	if (auto ControlledPawn = Cast<APingPongPlayer>(GetPawn()))
	{
		ControlledPawn->MovePlatformRight(Value);
	}
}

// Call move forward in pawn
void APingPongPlayerController::MoveForward(float Value)
{
	if (auto ControlledPawn = Cast<APingPongPlayer>(GetPawn()))
	{
		ControlledPawn->MovePlatformForward(Value);
	}
}
