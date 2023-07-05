// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//Allows the PlayerController to set up custom input bindings.
	virtual void SetupInputComponent() override;

private:
	// Call move right in pawn
	UFUNCTION()
	void MoveRight(float Value);

	// Call move forward in pawn
	UFUNCTION()
	void MoveForward(float Value);
};
