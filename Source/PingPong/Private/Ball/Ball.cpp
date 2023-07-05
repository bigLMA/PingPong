// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABall::ABall()
	:ImpulseCoeficient(300.f), FirstImpulseCoeficient(500.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/** Initialize Components */
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetLinearDamping(1.f);
	Mesh->SetAngularDamping(0.5f);

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind on hit function
	Mesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

// Locate ball to default coordinates
// Launch first impulse
void ABall::Reset()
{
	// Reset position
	FVector ZeroCoordinates = FVector(0, 0, 50);
	SetActorLocation(ZeroCoordinates);

	// Push ball
	FVector Direction = FMath::VRand();
	Mesh->AddImpulse(Direction * FirstImpulseCoeficient, NAME_None, true);
}

// Returns the properties used for network replication,
// This needs to be overridden by all actor classes with native replicated properties
void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABall, Mesh);
}

// Called when hits
void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Get direction and normal 
	FVector Velocity = Mesh->GetComponentVelocity();
	FVector BallDirection = Velocity.GetSafeNormal();
	FVector SafeNormal = Hit.ImpactNormal.GetSafeNormal();

	// Calculate reflection vector
	FVector ReflectionVector = 2 * FVector::DotProduct(BallDirection, SafeNormal) * SafeNormal;

	// Apply impulse
	Mesh->AddImpulse(ReflectionVector * ImpulseCoeficient, NAME_None, true);
}