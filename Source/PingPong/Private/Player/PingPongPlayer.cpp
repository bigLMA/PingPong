// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PingPongPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "HUD/PingPongHUD.h"

// Sets default values
APingPongPlayer::APingPongPlayer()
	:PlaneSpeed(15.f), HUD(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/** Initialize components*/ 
	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	SetRootComponent(Pivot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Pivot);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	Plane->SetupAttachment(Pivot);
	Plane->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	bReplicates = true;
}

// Called when the game starts or when spawned
void APingPongPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Create HUD
	APlayerController* PlayerController = GetController<APlayerController>();

	if (HUDClass&&PlayerController)
	{
		HUD = CreateWidget<UPingPongHUD>(PlayerController, HUDClass);
		HUD->AddToViewport();
		HUD->Reset();
	}
}

// Returns the properties used for network replication,
// This needs to be overridden by all actor classes with native replicated properties
void APingPongPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongPlayer, Plane);
}

// Input function, message server that platform is moving right
void APingPongPlayer::MovePlatformRight(float Value)
{
	Server_MovePlatformRight(Value);
}

// Input function, message server that platform is moving forward
void APingPongPlayer::MovePlatformForward(float Value)
{
	Server_MovePlatformForward(Value);
}

// Call update score on server
void APingPongPlayer::Server_UpdateScore_Implementation(int32 NewScore, bool bIsFirstPlayer)
{
	if (HasAuthority())
	{
		Multicast_UpdateScore(NewScore, bIsFirstPlayer);
	}
}

// Update Score
void APingPongPlayer::Multicast_UpdateScore_Implementation(int32 NewScore, bool bIsFirstPlayer)
{
	if (HUD)
	{
		HUD->ChangeScore(NewScore, bIsFirstPlayer);
	}
}

// Call move right on server
void APingPongPlayer::Server_MovePlatformRight_Implementation(float Value)
{
	if (HasAuthority())
	{
		FVector Movement = FVector(0, Value * PlaneSpeed, 0);
		Plane->AddLocalOffset(Movement, true);

		Client_MovePlatformRight(Value);
	}
}

// Call move forward on server
void APingPongPlayer::Server_MovePlatformForward_Implementation(float Value)
{
	if (HasAuthority())
	{
		FVector Movement = FVector(Value * PlaneSpeed, 0, 0);
		Plane->AddLocalOffset(Movement, true);

		Client_MovePlatformForward(Value);
	}
}

// Move platform right
void APingPongPlayer::Client_MovePlatformRight_Implementation(float Value)
{
	FVector Movement = FVector(0, Value * PlaneSpeed, 0);
	Plane->AddLocalOffset(Movement, true);
}

// Move platform forward
void APingPongPlayer::Client_MovePlatformForward_Implementation(float Value)
{
	FVector Movement = FVector(Value * PlaneSpeed, 0, 0);
	Plane->AddLocalOffset(Movement, true);
}