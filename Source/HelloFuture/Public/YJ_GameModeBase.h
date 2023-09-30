// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YJ_GameModeBase.generated.h"

UCLASS()
class HELLOFUTURE_API AYJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// ����â�� ����ȣ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Numbering System")
		int32 WaitingNumber = 1;

public:
	// ����â�� ����ȣ ���ϱ�
	UFUNCTION(BlueprintCallable)
		void AddWaitingNumber();
	// ����â�� ����ȣ ����
	UFUNCTION(BlueprintCallable)
		void MinusWaitingNumber();
	// ����â�� �� ���� �´��� Ȯ��
	UFUNCTION(BlueprintCallable)
		bool CheckMyOrder(class AHelloFutureCharacter* Player);
};
