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
	
	// 복제한 LocalPlayer에는 값이 저장되지 않는다.
	if(HasAuthority())
		RandValue = UChatLibrary::MakeRandValue();

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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Reset Call")); // RPC Server에서 전송한(Not Replicated) RandValue
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
	// 실행순위 - 3
	// 위젯에서 Server_SendChatMessage 함수 호출을통해 Validate가 true값을 반환한 경우 실행된다.
	// 각각의 Controller들이 실행됨(RPC = Server, WithValidation).

	UE_LOG(LogTemp, Error, TEXT("PlayerController - Server_SendChatMessage Call"));
	AChatGameMode* GameMode = Cast<AChatGameMode>(GetWorld()->GetAuthGameMode());

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
		// 서버는 LocalPlayer이면서 권한을 가지고있음.
		// 지금 클라이언트는 LocalPlayer가 아님.
		// 출력되는 값은 권한을 가지고 있으며, LocalPlayer의 값을 가지고 와야된다.

		Client_ReceiveMessage(Message, RandValue);
	}
}

bool AChatPlayerController::Server_SendChatMessage_Validate(const FString& Message)
{
	// 실행순위 - 2
	// WithValidation을 적용하면 전송 전 유효성 검사를 할 수 있다.
	// 멀티플레이어에서 플레이어의 공격력이 비정상적으로 높은 경우와 같은 유효성 검사.
	// Ex) if(Damage < 0 && Damage > MaxDamage) return false;

	UE_LOG(LogTemp, Error, TEXT("PlayerController - Send Validate Call"));

	return UChatLibrary::ValidSubmitMessage(Message);
}

void AChatPlayerController::Client_ReceiveMessage_Implementation(const FString& Message, const FString& TargetRandValue)
{
	// 실행순위 - 4
	// Server_SendChatMessage를 통해 각각의 클라이언트에서 실행된다.
	// 1. 위젯을 통해 입력한 문자열 출력
	// 2. 유효성 검사
	// 3. 결과 (S/B/OUT) 출력

	bool isEnd = false;

	UE_LOG(LogTemp, Error, TEXT("PlayerController - Client ReceiveMessage_Imple Call"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Sender + TEXT("(Local): ") + RandValue);		// 서버에서 복제한 컨트롤러(Not Replicated) RandValue
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Sender + TEXT("(Server) : ") + TargetRandValue); // RPC Server에서 전송한(Not Replicated) RandValue

	if (AChatPlayerState* PS = GetPlayerState<AChatPlayerState>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT("(PlayerState) : ") + PS->RandValue);	// 동기화를 위한 Replicated된 PlayerState의 RandValue

		if (PS->TryCount > 0 && UChatLibrary::CompareValue(Message, PS->RandValue))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT(" Win"));
			isEnd = true;
			Server_ResetGame();
			return;
		} 
		
		
		if (PS->TryCount <= 1 && !UChatLibrary::CompareValue(Message, PS->RandValue))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Sender + TEXT(" Lose"));
			isEnd = true;
			Server_ResetGame();
			return;
		}


		isEnd ? Server_ResetGame() : Server_DecreaseTryCount();
	}
}


