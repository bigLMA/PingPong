// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "Player/PingPongPlayerController.h"
#include "Player/PingPongPlayer.h"
#include "Ball/Ball.h"
#include "Goal/Goal.h"
#include "Kismet/GameplayStatics.h"


// GameMode Contructor
APingPongGameModeBase::APingPongGameModeBase()
	:Ball(nullptr), Player1Score(0), Player2Score(0)
{
	DefaultPawnClass = APingPongPlayer::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

// Called when the game starts or when spawned
void APingPongGameModeBase::BeginPlay()
{
	// Set timer to start a game
	GetWorld()->GetTimerManager().SetTimer(StartGameTimerHandle, this, &APingPongGameModeBase::StartGame, 0.3f, true);
}

// Check if can start game
// Starst game if can
void APingPongGameModeBase::StartGame()
{
	// Check if can start game
	if (GetNumPlayers() < 2)
	{
		return;
	}

	// Remove timer
	GetWorld()->GetTimerManager().ClearTimer(StartGameTimerHandle);

	// Spawn ball
	Server_SpawnBall();

	// Bind all goals scored events with game mode functionality
	TArray<AActor*> Goals;

	UGameplayStatics::GetAllActorsOfClass(this, AGoal::StaticClass(), Goals);

	for (auto Elem : Goals)
	{
		if (auto Goal = Cast<AGoal>(Elem))
		{
			Goal->OnGoalScored.AddUniqueDynamic(this, &APingPongGameModeBase::UpdateScore);
		}
	}
}

// Called after a successful login.This is the first place it is safe to call replicated functions on the PlayerController.
void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Message player if game is ready to play
	if (GetNumPlayers() == 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.5f, FColor::Cyan, TEXT("All players are in place. Let the game begin"));
	}
	else if (GetNumPlayers() == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.5f, FColor::Cyan, TEXT("Please wait for another player to connect"));
	}
}

// Message player pawns to update score in HUD
void APingPongGameModeBase::UpdateScore(bool bIsFirstPlayer)
{
	// Update score based on who scored
	if (bIsFirstPlayer)
	{
		++Player2Score;
	}
	else
	{
		++Player1Score;
	}

	// Update widgets
	int32 NewScore = (bIsFirstPlayer) ? Player2Score : Player1Score;
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(this, APingPongPlayer::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		if (auto Pawn = Cast<APingPongPlayer>(Actor))
		{
			Pawn->Server_UpdateScore(NewScore, bIsFirstPlayer);
		}
	}
}

// Call spawn ball on server
void APingPongGameModeBase::Server_SpawnBall_Implementation()
{
	if (HasAuthority())
	{
		Multicast_SpawnBall();
	}
}

// Spawn ball
void APingPongGameModeBase::Multicast_SpawnBall_Implementation()
{
	FVector SpawnLocation = FVector(0.f, 0.f, 51.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	Ball = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation, SpawnParams);
	Ball->Reset();
}