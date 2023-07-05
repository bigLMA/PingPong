// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

	// Rest ball position and add fist impulse
	void Reset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns the properties used for network replication,
	// This needs to be overridden by all actor classes with native replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called when hits
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Ball mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	// Impulse multiplier applied on hit
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Impulse Coeficient")
	float ImpulseCoeficient;

	// Impulse multiplier applied on game start
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Impulse Coeficient")
	float FirstImpulseCoeficient;
};