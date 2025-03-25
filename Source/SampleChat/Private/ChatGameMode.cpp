// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatGameMode.h"
#include "ChatPlayerController.h"
#include "ChatPlayerState.h"

AChatGameMode::AChatGameMode()
{
	PlayerStateClass = AChatPlayerState::StaticClass();
}

void AChatGameMode::SendMessageAllClients(const FString& Message)
{
	// 실행순위 - 4
	// PC에서 호출한 해당 함수호출.
	// 서버로 전달하기 전, 메시지 전달을 위한 함수.
	UE_LOG(LogTemp, Error, TEXT("Game Mode - SendMessageAllClients Call"));
	Client_BroadcastMessage(Message);
	//Multicast_BroadcastMessage(Message);
}

void AChatGameMode::Client_BroadcastMessage_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Error, TEXT("Game Mode - Client_BroadcastMessage Call"));

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AChatPlayerController* Controller = Cast<AChatPlayerController>(*It);
		if (Controller && Controller->IsLocalController())
		{
			//Controller->Client_ReceiveMessage(Message);
		}
	}
}

void AChatGameMode::Multicast_BroadcastMessage_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Error, TEXT("Game Mode - Multicast_BroadcastMessage Call"));

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AChatPlayerController* Controller = Cast<AChatPlayerController>(*It);
		if (Controller && Controller->IsLocalController())
		{
			//Controller->Client_ReceiveMessage(Message);
		}
	}
}
