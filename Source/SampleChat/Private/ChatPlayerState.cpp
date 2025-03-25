// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPlayerState.h"
#include "Net\UnrealNetwork.h"
#include "ChatLibrary.h"

AChatPlayerState::AChatPlayerState()
{
	bReplicates = true;
	TryCount = 3;
}

void AChatPlayerState::OnRep_PlayerNumbers()
{
	FString Sender = "Server";
	AController* AC = GetOwningController();
	if (AC)
	{
		Sender = GetOwningController()->HasAuthority() ? "Server" : "Guest";

	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT("SetUp RandValue : ") + RandValue);
}

void AChatPlayerState::OnRep_TryCount()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Left My TryCount : %d "),TryCount));
}

void AChatPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AChatPlayerState, RandValue);
	DOREPLIFETIME(AChatPlayerState, TryCount);
}
