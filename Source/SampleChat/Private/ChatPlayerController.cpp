// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPlayerController.h"
#include "ChatGameMode.h"
#include "ChatProjectWidget.h"
#include "ChatLibrary.h"
#include "ChatPlayerState.h"

void AChatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		UChatProjectWidget* ChatWidget = CreateWidget<UChatProjectWidget>(this, ChatWidgetClass);
		if (ChatWidget)
		{
			ChatWidget->AddToViewport();
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
		}
	}
	Sender = "Guest";
	
	if (HasAuthority())
	{
		AChatPlayerState* PS = GetPlayerState<AChatPlayerState>();
		if (PS)
		{
			PS->RandValue = UChatLibrary::MakeRandValue();
		}
	}

}

void AChatPlayerController::Server_ResetGame_Implementation()
{
	if (AChatPlayerState* PS = GetPlayerState<AChatPlayerState>())
	{
		PS->RandValue = UChatLibrary::MakeRandValue();
		PS->TryCount = 3;
	}
}

void AChatPlayerController::Server_DecreaseTryCount_Implementation()
{
	if (AChatPlayerState* PS = GetPlayerState<AChatPlayerState>())
	{
		PS->TryCount--;
	}
}


void AChatPlayerController::Server_SendChatMessage_Implementation(const FString& Message)
{
	if (HasAuthority() && IsLocalController())
	{
		Sender = "Host";
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController - Guest Call : %s"), *GetName());
	}

	if (HasAuthority())
	{
		Client_ReceiveMessage(Message, RandValue);
	}
}

bool AChatPlayerController::Server_SendChatMessage_Validate(const FString& Message)
{
	return UChatLibrary::ValidSubmitMessage(Message);
}

void AChatPlayerController::Client_ReceiveMessage_Implementation(const FString& Message, const FString& TargetRandValue)
{
	bool isEnd = false;

	if (AChatPlayerState* PS = GetPlayerState<AChatPlayerState>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT("(PlayerState) : ") + PS->RandValue);	// 동기화를 위한 Replicated된 PlayerState의 RandValue

		isEnd = UChatLibrary::CompareValue(Message, PS->RandValue);

		if (isEnd && PS->TryCount > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT(" Win"));
		}
		else if(!isEnd && PS->TryCount <= 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT(" Lose"));
			isEnd = true;
		}

		isEnd ? Server_ResetGame() : Server_DecreaseTryCount();
	}
}


