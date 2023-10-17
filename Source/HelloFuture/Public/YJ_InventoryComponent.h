// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YJ_InventoryComponent.generated.h"

// UI�� ������Ʈ �ϱ�����, �������Ʈ���� ���⿡ ���ε� �� ����.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaxUpdated);

// ������ ��ü�� �������� ���� �ε����� ���� enum
UENUM(BlueprintType)
enum class EItemEnum : uint8
{
	NONE = 0,
	Apple,
	ClothingHelmet,
	ClothingVest,
	CornItem,
	CornSeed,
	Radish,
	Lemon,
	Pumpkin,
	PumpkinSeed,
	WaterMelon,
	Wheat,
	WheatSeed,
	RadishSeed,
	WaitingTicket,
	Fertilizer,
	Fertilizer2,
	MagicPowder,
	Tonic,
	E_MAX,
};

// ����
USTRUCT(Atomic, BlueprintType)
struct FBankBookStruct
{
	GENERATED_BODY()

	// ������ ������ �ִ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		bool bHaveBankBook = false;
	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		int32 BankBookInterest = 0;
	// ���� ���� �� �� ���� ��¥
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		int32 BankBookPastDate = 0;
	// ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		float BankBookPercent = 0.01;
};

// ����
USTRUCT(Atomic, BlueprintType)
struct FLoanStruct
{
	GENERATED_BODY()

	// ������ �߾�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		bool bHaveBorrowedLoan = false;
	// ���� �� ���� ������� �ִ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		bool bUnpaidLoan = false;
	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 LoanInterest = 0;
	// ���� �� ���� ��¥
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 LoanPastDate = 0;
	// ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		float LoanPercent = 0.05;
	// ���� �����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 LoanValue = 100000;
};

// ����
USTRUCT(Atomic, BlueprintType)
struct FTaxStruct
{
	GENERATED_BODY()

	// ���� �� ���� ������ �ִ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		bool bUnpaidTax = false;
	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 TaxInterest;
	// ���� ���� �� ���� ��¥
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 TaxPastDate = 0;
	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		float TaxPercent;
	// ���ݰ����� ��ȣ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 TaxContent = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOFUTURE_API UYJ_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** �Ӽ� �ʱⰪ ���� */
	UYJ_InventoryComponent();
	void BeginPlay();

	/** ������ ���� �Լ� */
	// �κ��丮�� ������ �߰�1
	UFUNCTION(BlueprintCallable)
		bool AddItem(class UYJ_Item* Item);
	// �κ��丮�� ������ �߰�2
	UFUNCTION(BlueprintCallable)
		bool AddItem2(EItemEnum Item);
	// �κ��丮�� ������ �߰�3
	//UFUNCTION(BlueprintCallable)
	//	bool AddItem3(TSubclassOf<class UYJ_Item> ItemClass, int32 Num = 1);
	// ������ŭ �κ��丮�� ������ �߰�
	UFUNCTION(BlueprintCallable)
		bool AddItemByNumber(EItemEnum Item, int32 Num);
	// �κ��丮�� ������ ����1
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(class UYJ_Item* Item);
	// �κ��丮�� ������ ����2
	UFUNCTION(BlueprintCallable)
		bool RemoveItem2(EItemEnum Item);
	//// �κ��丮�� ������ ����3
	//UFUNCTION(BlueprintCallable)
	//	bool RemoveItem3(TSubclassOf<class UYJ_Item> ItemClass, int32 Num = 1);
	// ������ŭ �κ��丮�� ������ ����
	UFUNCTION(BlueprintCallable)
		bool RemoveItemByNumber(EItemEnum Item, int32 Num);
	// ������ enum -> ������ ��ü�� ��ȯ
	UFUNCTION(BlueprintCallable)
		class UYJ_Item* EnumIndexToItem(EItemEnum Item);
	// �ش� �������� ������ �ִ��� Ȯ��
	UFUNCTION(BlueprintCallable)
		bool CheckItemAsYJ_Item(class UYJ_Item* Item);
	// ������ enum���� �ش� �������� ������ �ִ��� Ȯ��
	UFUNCTION(BlueprintCallable)
		bool CheckItemAsEnum(EItemEnum Item);

	/**�� ���� �Լ�*/
	// ���� ���ϰų� ����
	UFUNCTION(BlueprintCallable)
		bool AddCash(int32 AddPrice);
	// �����ܱ� ���ϰų� ����
	UFUNCTION(BlueprintCallable)
		bool AddAccountBalance(int32 AddPrice);

	/**��������, �����, ���� ���� �Լ�*/
	// �������� ������Ʈ
	UFUNCTION(BlueprintCallable)
		bool UpdateBankBookInterest();
	// ����� ������Ʈ
	UFUNCTION(BlueprintCallable)
		bool UpdateLoan();
	// ���ƾ� �� ����� ��ȯ
	UFUNCTION(BlueprintCallable)
		int32 GetTotalLoanAmount();
	// ���� ������Ʈ
	UFUNCTION(BlueprintCallable)
		bool UpdateTax();

public:
	/** �κ��丮 ĭ ���� */
	// �κ��丮 ĭ �뷮
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;
	// �κ��丮 ����ĭ ����
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 ColumnLength;
	// �κ��丮 ����ĭ ����
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 RowLength;

	/** ������ �ִ� �͵� ���� */
	// ������ �ִ� �κ��丮 ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<class UYJ_Item*> Items;
	// ������ �ִ� �κ��丮 ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		int32 ItemCnt;
	// �����ܰ�
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 AccountBalance;
	// �����ܰ�
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 Cash;

	/** ������ �ִ� �͵� ���� */
	/*
	USTRUCT(Atomic, BlueprintType)
	struct ItemStruct
	{
		// ������ Ŭ����
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
			TSubclassOf<class UYJ_Item> ItemClass;
		// ������ ����
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
			int32 ItemNumber;
	};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<ItemStruct> ItemStructArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TMap<TSubclassOf<class UYJ_Item>, int32> ItemIndexMap;
	*/

	/** ����, ����, ���� ���ڿ� ���� ���� */
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		FBankBookStruct BankBook;
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		FLoanStruct Loan;
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		FTaxStruct Tax;

	/** ��������Ʈ */
	// �κ��丮 ��������Ʈ
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated	OnInventoryUpdated;
	// ���� ��������Ʈ
	UPROPERTY(BlueprintAssignable, Category = "Tax")
		FOnTaxUpdated OnTaxUpdated;
};
