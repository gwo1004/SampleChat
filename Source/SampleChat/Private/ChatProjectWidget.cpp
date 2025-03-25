// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatProjectWidget.h"
#include "ChatPlayerController.h"


void UChatProjectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChatTextBox && !ChatTextBox->OnTextCommitted.IsBound())
	{
		ChatTextBox->OnTextCommitted.AddDynamic(this, &UChatProjectWidget::CommitText);
	}
}

void UChatProjectWidget::CommitText(const FText& Text, ETextCommit::Type CommitMethod)
{


	// 실행순위 - 1
	// 클라이언트가 위젯을 통해 플레이어 컨트롤러에게 해당 내용 전달.
	// Delegate를 사용한 이벤트 기반으로도 가능.

	//UE_LOG(LogTemp, Error, TEXT("Widget - Commit Text Call"));
	//AChatPlayerController* PC = Cast<AChatPlayerController>(GetOwningPlayer());
	//if (PC && PC->IsLocalPlayerController() && CommitMethod == ETextCommit::OnEnter)
	//{
	//	PC->Server_SendChatMessage(Text.ToString());
	//	ChatTextBox->SetText(FText::GetEmpty());
	//}

	// 플레이어 컨트롤러 가져오기
	APlayerController* PC = GetOwningPlayer();

	// 리슨 서버 환경에서는 서버의 PlayerController도 실행되므로 로컬 컨트롤러인지 확인
	if (PC && PC->IsLocalController() && CommitMethod == ETextCommit::OnEnter)
	{
		AChatPlayerController* ChatPC = Cast<AChatPlayerController>(PC);
		if (ChatPC)
		{
			UE_LOG(LogTemp, Error, TEXT("Widget - Commit Text Call"));
			ChatPC->Server_SendChatMessage(Text.ToString());
		}
	}

	ChatTextBox->SetText(FText::GetEmpty());
}
