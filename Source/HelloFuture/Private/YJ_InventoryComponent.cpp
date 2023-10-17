// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_GameInstance.h"
#include "YJ_GameModeBase.h"
#include "YJ_Item.h"
#include "YJ_WaitingTicketItem.h"

UYJ_InventoryComponent::UYJ_InventoryComponent()
{
	AccountBalance = 0;
	Cash = 10000;

	ColumnLength = 7;
	RowLength = 3;
	Capacity = ColumnLength * RowLength; // 20
}

void UYJ_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UYJ_InventoryComponent::AddItem(UYJ_Item* Item)
{
	// �κ��丮 â�� �� ���ų� ������ Item �� ��ȿ���� ������ �Ʒ� ���� �������� ����.
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	// Item�� ���� ���ǥ�� ��, Items�� ���ǥ�� ������ �Ʒ� ���� �������� ����.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(Item);
	if (waitingTicketItem)
	{
		for (auto yjItem : Items)
		{
			if (Cast<UYJ_WaitingTicketItem>(yjItem) != nullptr)
			{
				return false;
			}
		}

		UWorld* const World = GetWorld();
		AYJ_GameModeBase* GameMode;
		if (World) {
			GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
			waitingTicketItem->ItemWaitingNumber = GameMode->WaitingNumber + 1;
		}
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	// ���ε� �� �Լ��� ����: �κ��丮 UI ������Ʈ
	OnInventoryUpdated.Broadcast();

	return true;
}

// �����ν��Ͻ��� AllItems �迭���� Item��° YJ_Item �� �����ͼ� add
bool UYJ_InventoryComponent::AddItem2(EItemEnum Item)
{
	// �κ��丮 â�� �� ���� �Ʒ� ���� �������� ����.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// �����ν��Ͻ� ��������
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// ������ ��������
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	// Item�� ���� ���ǥ�� ��, Items�� ���ǥ�� ������ �Ʒ� ���� �������� ����.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(item);
	if (waitingTicketItem)
	{
		for (auto yjItem : Items)
		{
			if (Cast<UYJ_WaitingTicketItem>(yjItem) != nullptr)
			{
				return false;
			}
		}

		UWorld* const World = GetWorld();
		AYJ_GameModeBase* GameMode;
		if (World) {
			GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
			if (!GameMode) return false;
			waitingTicketItem->ItemWaitingNumber = GameMode->WaitingNumber;
		}
	}

	// ������ �߰��ϱ�
	if(item->Count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->ItemIndex = idx;
		item->InventoryIndex = ItemCnt;
		item->Count = 1;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->Count++;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::AddItemByNumber(EItemEnum Item, int32 Num)
{
	// �κ��丮 â�� �� ���� �Ʒ� ���� �������� ����.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// �����ν��Ͻ� ��������
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// ������ ��������
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	// Item�� ���� ���ǥ�� ��, Items�� ���ǥ�� ������ �Ʒ� ���� �������� ����.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(item);
	if (waitingTicketItem)
	{
		for (auto yjItem : Items)
		{
			if (Cast<UYJ_WaitingTicketItem>(yjItem) != nullptr)
			{
				return false;
			}
		}

		UWorld* const World = GetWorld();
		AYJ_GameModeBase* GameMode;
		if (World) {
			GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
			if (!GameMode) return false;
			waitingTicketItem->ItemWaitingNumber = GameMode->WaitingNumber + 1;
		}
	}

	// ������ �߰��ϱ�
	if (item->Count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->ItemIndex = idx;
		item->InventoryIndex = ItemCnt;
		item->Count += Num;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->Count += Num;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}
/*
bool UYJ_InventoryComponent::AddItem3(TSubclassOf<UYJ_Item> ItemClass, int32 Num)
{
	// �κ��丮 â�� �� ���� �Ʒ� ���� �������� ����.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// ������ ��������
	UYJ_Item* Item = ItemClass.GetDefaultObject();

	// Item�� ���� ���ǥ�� ��, Items�� ���ǥ�� ������ �Ʒ� ���� �������� ����.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(Item);
	if (waitingTicketItem)
	{
		for (auto yjItem : Items)
		{
			if (Cast<UYJ_WaitingTicketItem>(yjItem) != nullptr)
			{
				return false;
			}
		}

		// ���Ӹ�� �����ͼ�, ��������� ����ȣ ������Ű��.
		UWorld* World = GetWorld();
		if (!World) return false;
		if (World) {
			AYJ_GameModeBase* GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
			if (!GameMode) return false;
			waitingTicketItem->ItemWaitingNumber = GameMode->WaitingNumber + 1;
		}
	}

	// ������ �߰��ϱ�
	if(!ItemIndexMap.Contains(ItemClass))
	{
		ItemStructArray.Add({ ItemClass, 1 });
		ItemIndexMap.Add(ItemClass, 1);
		ItemCnt++;
	}
	else
	{
		ItemStructArray.Add({ ItemClass, 1 });
		ItemIndexMap.Add(ItemClass, 1);
		Item->Count += Num;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}
*/

bool UYJ_InventoryComponent::RemoveItem(UYJ_Item* Item)
{
	// �κ��丮 â�� ��ų� ������ Item �� ��ȿ���� ������ �Ʒ� ���� �������� ����.
	if (Items.Num() <= 0 || !Item)
	{
		return false;
	}

	Item->OwningInventory = nullptr;
	Item->World = nullptr;
	Items[ItemCnt] = nullptr;
	//Items.RemoveSingle(Item);
	OnInventoryUpdated.Broadcast();
	return true;
}

// �����ν��Ͻ��� AllItems �迭���� Item��° YJ_Item �� �����ͼ� remove
bool UYJ_InventoryComponent::RemoveItem2(EItemEnum Item)
{
	// �κ��丮 â�� ��� �Ʒ� ���� �������� ����.
	if (ItemCnt <= 0)
	{
		return false;
	}

	// �����ν��Ͻ� ��������
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// ������ ��������
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	// ������ �����
	if (item->Count <= 1)
	{
		item->OwningInventory = nullptr;
		item->World = nullptr;
		item->ItemIndex = idx;
		item->InventoryIndex = -1;
		item->Count = 0;
		Items.RemoveSingle(item);
		ItemCnt--;
	}
	else
	{
		item->Count--;
	}

	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItemByNumber(EItemEnum Item, int32 Num)
{
	// �κ��丮 â�� ��� �Ʒ� ���� �������� ����.
	if (ItemCnt <= 0)
	{
		return false;
	}

	// �����ν��Ͻ� ��������
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// ������ ��������
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	if (item->Count < Num) return false;

	// ������ �����
	if (item->Count - Num <= 0)
	{
		item->OwningInventory = nullptr;
		item->World = nullptr;
		item->ItemIndex = idx;
		item->InventoryIndex = -1;
		item->Count = 0;
		//Items[ItemCnt] = nullptr;
		Items.RemoveSingle(item);
		//Items.SetNum(Capacity);
		ItemCnt--;
	}
	else
	{
		//Items[item->InventoryIndex]->Count--;
		item->Count -= Num;
	}
	OnInventoryUpdated.Broadcast();

	return true;
}
/*
bool UYJ_InventoryComponent::RemoveItem3(TSubclassOf<UYJ_Item> ItemClass, int32 Num)
{
	// �κ��丮 â�� ��� �Ʒ� ���� �������� ����.
	if (ItemCnt <= 0)
	{
		return false;
	}

	// ������ ��������
	UYJ_Item* Item = ItemClass.GetDefaultObject();

	if (Item->Count < Num) return false;

	// ������ �����
	if (Item->Count - Num <= 0)
	{
		Item->OwningInventory = nullptr;
		Item->Count = 0;
		//Items[ItemCnt] = nullptr;
		Items.RemoveSingle(Item);
		//Items.SetNum(Capacity);
		ItemCnt--;
	}
	else
	{
		//Items[item->InventoryIndex]->Count--;
		Item->Count -= Num;
	}
	OnInventoryUpdated.Broadcast();

	return true;
}
*/
UYJ_Item* UYJ_InventoryComponent::EnumIndexToItem(EItemEnum Item)
{
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];
	if (item)
	{
		for (auto itm : Items)
		{
			if (itm == item)
			{
				return itm;
			}
		}
	}
	return nullptr;
}

bool UYJ_InventoryComponent::CheckItemAsYJ_Item(UYJ_Item* Item)
{
	if (Item->InventoryIndex >= 0) return true;
	else return false;
}

bool UYJ_InventoryComponent::CheckItemAsEnum(EItemEnum Item)
{
	UYJ_Item* item = UYJ_InventoryComponent::EnumIndexToItem(Item);

	for (auto itm : Items)
	{
		if (itm == item)
		{
			return true;
		}
	}

	return false;
}

bool UYJ_InventoryComponent::AddCash(int32 AddPrice)
{
	if (Cash + AddPrice >= 0)
	{
		Cash = Cash + AddPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::AddAccountBalance(int32 AddPrice)
{
	if (AccountBalance + AddPrice >= 0)
	{
		AccountBalance = AccountBalance + AddPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::UpdateBankBookInterest()
{
	// ������ ���ٸ� ����
	if (BankBook.bHaveBankBook == false) return true;
	// �������� ���� ���ϰ�, 7���� ������ �����ֱ�
	BankBook.BankBookPastDate++;
	BankBook.BankBookInterest += AccountBalance * BankBook.BankBookPercent / 7;

	if (BankBook.BankBookPastDate >= 7)
	{
		AccountBalance += BankBook.BankBookInterest;
		BankBook.BankBookInterest = 0;
		BankBook.BankBookPastDate = 0;
	}

	return true;
}

bool UYJ_InventoryComponent::UpdateLoan()
{
	// ���� ���� ������� ������ ����
	if (Loan.bUnpaidLoan == false)
	{
		Loan.LoanPastDate = 0;
		Loan.LoanInterest = 0;
		return true;
	}

	// ������� �����ʾҰ�, 7���� �������� ���ڰ� ����
	Loan.LoanPastDate++;
	if (Loan.LoanPastDate >= 7)
	{
		Loan.LoanInterest += Loan.LoanValue * Loan.LoanPercent;
	}

	return true;
}

int32 UYJ_InventoryComponent::GetTotalLoanAmount()
{
	return Loan.LoanInterest + Loan.LoanValue;
}

bool UYJ_InventoryComponent::UpdateTax()
{
	// ���� �������� 7�� ��������, ������ �������� ���ݰ��
	Tax.TaxPastDate++;
	if (Tax.TaxPastDate % 7 == 0)
	{
		Tax.TaxContent = FMath::RandRange(0, 4);

		switch (Tax.TaxContent)
		{
		case 0:
			Tax.TaxPercent = 0.03;
			break;
		case 1:
			Tax.TaxPercent = 0.05;
			break;
		case 2:
			Tax.TaxPercent = 0.08;
			break;
		case 3: 
			Tax.TaxPercent = 0.1;
			break;
		case 4:
			Tax.TaxPercent = 0.15;
			break;
		default:
			break;
		}

		Tax.TaxInterest = (int32)((AccountBalance + Cash) * Tax.TaxPercent);
		OnTaxUpdated.Broadcast();
	}

	return true;
}
