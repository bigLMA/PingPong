// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoalScored, bool, bFirstPlayer);

UCLASS()
class PINGPONG_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	// Delegate called when ball is inside goal
	UPROPERTY()
	FOnGoalScored OnGoalScored;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called on overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Goal mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	// Goal collision
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Goal Collision")
	class UBoxComponent* GoalCollision;

	// If goal owner is first player
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Is First player?")
	bool bIsFirstPlayer;
};
