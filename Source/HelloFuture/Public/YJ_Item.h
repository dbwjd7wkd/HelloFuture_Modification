// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YJ_Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class HELLOFUTURE_API UYJ_Item : public UObject
{
	GENERATED_BODY()
	
public:
	// ���� ��������
	virtual class UWorld* GetWorld() const { return World; };

	// �Ӽ� �ʱⰪ ����
	UYJ_Item();

public:
	// ���� ����
	UPROPERTY(Transient)
		class UWorld* World;
	//  �κ��丮
	UPROPERTY()
		class UYJ_InventoryComponent* OwningInventory;

	/**������ ����*/
	// ����� ������ ī�װ� (ex. use, equip, etc)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText Category;
	// ������ �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;
	// ������ �̸�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;
	// ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;
	// ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 Price;
	// ������ ���� ���� �ּڰ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MinPrice;
	// ������ ���� ���� �ִ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MaxPrice;
	// ������ �ε���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ItemIndex;

	/** �÷��̾��� ���� ������ �κ��丮 ����*/
	// ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 Count;
	// ������ �κ��丮 �ε���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 InventoryIndex;

};
