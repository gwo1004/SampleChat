// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ChatGameState.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API AChatGameState : public AGameState
{
	GENERATED_BODY()

public:
	AChatGameState();

public:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerNumbers)
	FString RandValue;


protected:
	UFUNCTION()
	void OnRep_PlayerNumbers();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
