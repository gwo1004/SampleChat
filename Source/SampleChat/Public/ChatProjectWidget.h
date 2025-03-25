// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "ChatProjectWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API UChatProjectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ChatTextBox;

public:
	UFUNCTION()
	void CommitText(const FText& Text, ETextCommit::Type CommitMethod);
};
