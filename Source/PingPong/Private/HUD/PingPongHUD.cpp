// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PingPongHUD.h"
#include "Components/TextBlock.h"

// Apply default score to text labels
void UPingPongHUD::Reset()
{
	Player1ScoreLabel->SetText(FText::FromString(FString::FromInt(0)));
	Player2ScoreLabel->SetText(FText::FromString(FString::FromInt(0)));
}

// Display new score
void UPingPongHUD::ChangeScore(int32 InNewScore, bool bIsFirstPlayer)
{
	// Change score display based on who scored
	if (bIsFirstPlayer)
	{
		Player2ScoreLabel->SetText(FText::FromString(FString::FromInt(InNewScore)));
	}
	else
	{
		Player1ScoreLabel->SetText(FText::FromString(FString::FromInt(InNewScore)));
	}
}
