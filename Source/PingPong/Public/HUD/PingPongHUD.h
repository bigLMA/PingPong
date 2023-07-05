// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PingPongHUD.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UPingPongHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Display default score to text labels
	void Reset();

	// Display new score
	void ChangeScore(int32 InNewScore, bool bIsFirstPlayer);

protected:
	// Score text label of player 1
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Player1ScoreLabel;
	
	// Score text label of player 2
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Player2ScoreLabel;
};
