// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "YJ_Item.h"
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
	Apple = 0,
	ClothingHelmet,
	ClothingVest,
	CornItem,
	CornSeed,
	Radish,
	Bread,
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
};

// ��������
USTRUCT(Atomic, BlueprintType)
struct FBankBookInterestStruct
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
	// �Ӽ��� �ʱⰪ ����
	UYJ_InventoryComponent();

	virtual void BeginPlay() override;
	// ������ ���� �Լ�
	UFUNCTION(BlueprintCallable)
		bool AddItem(UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool AddItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool AddItem3(TSubclassOf<UYJ_Item> ItemClass);
	UFUNCTION(BlueprintCallable)
		bool AddItemByNumber(EItemEnum Item, int32 Num);

	UFUNCTION(BlueprintCallable)
		bool RemoveItem(UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem3(TSubclassOf<UYJ_Item> ItemClass);
	UFUNCTION(BlueprintCallable)
		bool RemoveItemByNumber(EItemEnum Item, int32 Num);

	UFUNCTION(BlueprintCallable)
		UYJ_Item* EnumIndexToItem(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool CheckItemAsYJ_Item(UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool CheckItemAsEnum(EItemEnum Item);

	// �� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		bool AddCash(int32 AddPrice);
	UFUNCTION(BlueprintCallable)
		bool AddAccountBalance(int32 AddPrice);

	// �������� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		bool UpdateBankBookInterest();
	// ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		bool UpdateLoan();
	UFUNCTION(BlueprintCallable)
		int32 GetTotalLoanAmount();
	// ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		bool UpdateTax();

public:
	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<UYJ_Item*> DefaultItems;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 ColumnLength;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 RowLength;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 AccountBalance;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		int32 Cash;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated	OnInventoryUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Tax")
		FOnTaxUpdated OnTaxUpdated;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
		FName State; // add, remove

	// �κ��丮 ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<UYJ_Item*> Items;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
		int32 ItemCnt;

	// ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		FBankBookInterestStruct BankBook;
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		FLoanStruct Loan;
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		FTaxStruct Tax;

	//// SaveGame�� ���� �κ��丮 ������ ����
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryCnt; // �κ��丮�� �� ������ ����

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryIdx; // �κ��丮�� �� ������ �ε���
};
