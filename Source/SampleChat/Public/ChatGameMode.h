// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API AChatGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AChatGameMode();

public:
	void SendMessageAllClients(const FString& Message);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_BroadcastMessage(const FString& Message);

	UFUNCTION(Client, Reliable)
	void Client_BroadcastMessage(const FString& Message);
};
