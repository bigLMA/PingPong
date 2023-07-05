// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// GameMode Contructor
	APingPongGameModeBase();

	// Called after a successful login.
	// This is the first place it is safe to call replicated functions on the PlayerController
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ball class to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Impulse Coeficient")
	TSubclassOf<class ABall> BallClass;

	// Ask server to begin spawn ball
	UFUNCTION(Server, Reliable)
	void Server_SpawnBall();

	// Spawn ball
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnBall();

private:
	// Message player pawns to update score in HUD
	UFUNCTION()
	void UpdateScore(bool bIsFirstPlayer);

	// Check if can start game
	// Starst game if can
	void StartGame();

	// Ball
	UPROPERTY()
	class ABall* Ball;

	/** Score values */
	int32 Player1Score;
	int32 Player2Score;

	// Timer handle to check if can start game
	FTimerHandle StartGameTimerHandle;
};
