// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class HELLOFUTURE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	virtual void OnConstruction(const FTransform& Transform);
	// �θ� �������Ʈ Construction Script���� ȣ�� �ʼ�.
	UFUNCTION(BlueprintCallable)
		void Construct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// ������ ��� ���: ���� �����Լ�
	UFUNCTION()
		virtual void UseItem() PURE_VIRTUAL(AItem::UseItem, );

private:
	UFUNCTION()
		void PickUpItem();

protected:
	/**������ ��ü*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCapsuleComponent* Capsule;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* StaticMesh;

public:
	/**������ ����*/
	// ������ �޽�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* NewMesh;
	// ������ �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;
	// ������ �̸�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;
	// ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;
	// ������ ��� �迭
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//	TArray<TSubclassOf<class UItemAffect>> AffectArray;
	// ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 Price;
	// ������ ���� ���� �ּڰ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MinPrice;
	// ������ ���� ���� �ִ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MaxPrice;

	// ������ �ݴ� ���� �ִϸ��̼�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UAnimMontage* PickingUpMontage;
	// ������ �ֿ� �� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class USoundCue* PickingUpSound;

private:
	/** ������ ����*/
	UPROPERTY()
		class AHelloFutureCharacter* Player;

};
