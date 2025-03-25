// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatGameState.h"
#include "ChatLibrary.h"
#include "Net\UnrealNetwork.h"

AChatGameState::AChatGameState()
{
	bReplicates = true;
}

void AChatGameState::OnRep_PlayerNumbers()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SetUp RandValue : ") + RandValue);
}

void AChatGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChatGameState, RandValue);
}
