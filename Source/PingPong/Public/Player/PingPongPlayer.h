// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PingPongPlayer.generated.h"

UCLASS()
class PINGPONG_API APingPongPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APingPongPlayer();

	// Input function, message server that platform is moving right
	void MovePlatformRight(float Value);

	// Input function, message server that platform is moving forward
	void MovePlatformForward(float Value);

	// Call update score on server
	UFUNCTION(Server, Reliable)
	void Server_UpdateScore(int32 NewScore, bool bIsFirstPlayer);

	// Update Score
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateScore(int32 NewScore, bool bIsFirstPlayer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns the properties used for network replication,
	// This needs to be overridden by all actor classes with native replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Root Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pivot") // TODO comments
	USceneComponent* Pivot;

	// Spring arm component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	// Plane, player instrument to manipulate ball movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Plane")
	UStaticMeshComponent* Plane;

	// Determines speed of plane, controlled by player
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plane")
	float PlaneSpeed;

	// HUD class to create
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UPingPongHUD> HUDClass;

private:
	// Call move right on server
	UFUNCTION(Server, Reliable)
	void Server_MovePlatformRight(float Value);

	// Call move forward on server
	UFUNCTION(Server, Reliable)
	void Server_MovePlatformForward(float Value);

	// Move platform right
	UFUNCTION(Client, Reliable)
	void Client_MovePlatformRight(float Value);

	// Move platform forward
	UFUNCTION(Client, Reliable)
	void Client_MovePlatformForward(float Value);

	// HUD
	UPROPERTY()
	class UPingPongHUD* HUD;
};
