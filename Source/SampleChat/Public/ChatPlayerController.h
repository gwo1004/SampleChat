// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API AChatPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();
public:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendChatMessage(const FString& Message);

	UFUNCTION(Server, Reliable)
	void Server_DecreaseTryCount();

	UFUNCTION(Server, Reliable)
	void Server_ResetGame();

	UFUNCTION(Client, Reliable)
	void Client_ReceiveMessage(const FString& Message, const FString& TargetRandValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UChatProjectWidget> ChatWidgetClass;


private:
	FString RandValue;
	FString Sender;

};
