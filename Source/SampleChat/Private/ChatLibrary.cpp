// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatLibrary.h"

// 유효성 검사 관련 로직
bool UChatLibrary::ValidSubmitMessage(const FString& Message)
{
	FString ValidNum = Message;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sender Input Message : ") + Message);

	// 시작 '/' 검사
	if (!ValidNum.StartsWith(TEXT("/")))
	{
		FString FailMessage = ValidNum + TEXT(": Is Not Contains '/' Or Not First Word");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FailMessage);

		return false;
	}

	ValidNum.RemoveAt(0);

	// '/' 제거 후 3자리수 체크
	if (ValidNum.Len() != 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ValidNum + TEXT(": Is Not 3 Length."));
		return false;
	}
	
	// Int형으로 변환이 가능한지
	if (!CanAtoi(ValidNum))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ValidNum + TEXT(": Is Not Valid Number."));
		return false;
	}

	//int32 Number = FCString::Atoi(*ValidNum);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AtoI : ") + FString::FromInt(Number));


	return true;
}

// Server-Client간 번호 비교 로직
// S : 서버 - 플레이어간 자리수와 값이 동일한 경우
// B : 값은 동일하지만 자리수가 다른 경우
// OUT : 값이 존재하지 않는 경우
bool UChatLibrary::CompareValue(const FString& Message, const FString& RandValue)
{
	FString ValidNum = Message;
	ValidNum.RemoveAt(0);

	FBullsAndCowsCount Count;
	for (int i = 0; i < ValidNum.Len(); i++)
	{
		if (ValidNum[i] == RandValue[i])
		{
			Count.Strike++;
		}
		else if (RandValue.Contains(FString(1, &ValidNum[i])))
		{
			Count.Ball++;
		}
		else
		{
			Count.Out++;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,
	FString::Printf(TEXT("SBO Count : %d / %d / %d"),
		Count.Strike,
		Count.Ball,
		Count.Out));

	return Count.Strike >= 3;
}

// isdigit를 사용한 타입 검사
bool UChatLibrary::CanAtoi(FString ValidNumber)
{
	for (auto& Num : ValidNumber)
	{
		if (!isdigit(Num))
		{
			return false;
		}
	}

	return true;
}

// 게임 시작 시 난수 생성 로직
FString UChatLibrary::MakeRandValue()
{
	TArray<int32> ArrayRandNum;
	FString RandValue;

	while (ArrayRandNum.Num() < 3)
	{
		int32 RandNum = FMath::RandRange(1, 9);

		if (ArrayRandNum.Contains(RandNum))
		{
			continue;
		}

		ArrayRandNum.Add(RandNum);
		RandValue.Append(FString::FromInt(RandNum));
	}

	return RandValue;
}

// 문자열 변환 Convert FString to int32
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/string-handling-in-unreal-engine
// https://devjino.tistory.com/252