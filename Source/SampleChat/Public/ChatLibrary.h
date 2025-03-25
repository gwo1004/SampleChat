// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChatLibrary.generated.h"

/**
 * 
 */

USTRUCT()
struct FBullsAndCowsCount
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Strike;

	UPROPERTY()
	int32 Ball;

	UPROPERTY()
	int32 Out;

	FBullsAndCowsCount()
		: Strike(0), Ball(0), Out(0)
	{
	}
};

UCLASS()
class SAMPLECHAT_API UChatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Project")
	static FString MakeRandValue();

	UFUNCTION(BlueprintCallable, Category = "Project")
	static bool ValidSubmitMessage(const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Project")
	static bool CompareValue(const FString& Message, const FString& RandValue);

private:
	static bool CanAtoi(FString ValidNumber);
};
