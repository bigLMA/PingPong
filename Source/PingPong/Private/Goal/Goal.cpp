// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal/Goal.h"
#include "Components/BoxComponent.h"
#include "Ball/Ball.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/** Initialize Components */
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GoalCollision = CreateDefaultSubobject<UBoxComponent>("Goal Collision");
	GoalCollision->SetupAttachment(Mesh);
	GoalCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap function
	GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);
}

// Called on overlap
void AGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		OnGoalScored.Broadcast(bIsFirstPlayer);
	}
}
