// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YJ_ATM.generated.h"

UCLASS()
class HELLOFUTURE_API AYJ_ATM : public AActor
{
	GENERATED_BODY()
	
public:
	// �ʱⰪ ����
	AYJ_ATM();
	virtual void BeginPlay() override;

	/** ������ */
	// ĳ���Ͱ� ATM�⿡ �������ϸ� ATM UI ����
	UFUNCTION() 
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// ĳ������ ATM�� �������� ������ ATM UI �����
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	/** ATM UI */
	// ATM UI ����
	UFUNCTION(BlueprintCallable)
		void ShowATMWidget();
	// ATM UI �����
	UFUNCTION(BlueprintCallable)
		void HideATMWidget();

public:
	// box�ݸ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ATM")
		class UBoxComponent* BoxCollision;
	// �޽�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ATM")
		class UStaticMeshComponent* StaticMesh;

	// ATM UI Ŭ����
	// @Warning �������Ʈ���� ATM UI Ŭ�������۷����� �־���� ��.
	// "WidgetBlueprint'/Game/YJ/UI/ATM/WBP_ATM'"
	UPROPERTY(EditDefaultsOnly, Category = "ATM")
		TSubclassOf<UUserWidget> ATMWidgetClass;

private:
	// ATM UI �ν��Ͻ�
	UPROPERTY(VisibleAnywhere)
		UUserWidget* ATMWidget;

	// ������ �� �÷��̾�
	UPROPERTY(VisibleAnywhere)
		class AHelloFutureCharacter* OverlapPlayer;

};
