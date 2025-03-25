// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ChatPlayerState.generated.h"

/**
 * 
 */


UCLASS()
class SAMPLECHAT_API AChatPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AChatPlayerState();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerNumbers)
	FString RandValue;

	UPROPERTY(ReplicatedUsing = OnRep_TryCount)
	int32 TryCount;

protected:
	UFUNCTION()
	void OnRep_PlayerNumbers();

	UFUNCTION()
	void OnRep_TryCount();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
