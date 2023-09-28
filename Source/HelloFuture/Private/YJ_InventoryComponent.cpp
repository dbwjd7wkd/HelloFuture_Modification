// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_InventoryComponent.h"
#include "YJ_Item.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_GameModeBase.h"
#include "YJ_WaitingTicketItem.h"
#include "YJ_GameModeBase.h"
#include "YJ_GameInstance.h"

// Sets default values for this component's properties
UYJ_InventoryComponent::UYJ_InventoryComponent()
{
	AccountBalance = 0;
	Cash = 10000;

	ColumnLength = 7;
	RowLength = 3;
	Capacity = ColumnLength * RowLength; // 20
}

// Called when the game starts
void UYJ_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UYJ_InventoryComponent::AddItem(UYJ_Item* Item)
{
	// 인벤토리 창이 다 차거나 들어오는 Item 이 유효하지 않으면 아래 내용 실행하지 않음.
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
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
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	State = "add";
	Items.Add(Item);
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

// 게임인스턴스의 AllItems 배열에서 Item번째 YJ_Item 을 가져와서 add
bool UYJ_InventoryComponent::AddItem2(EItemEnum Item)
{
	// 인벤토리 창이 다 차면 아래 내용 실행하지 않음.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->allItems[idx];

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
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
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber;
		}
	}

	// 아이템 추가하기
	State = "add";
	
	if(item->count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->itemIndex = idx;
		item->inventoryIndex = ItemCnt;
		item->count = 1;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->count++;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::AddItemByNumber(EItemEnum Item, int32 Num)
{
	// 인벤토리 창이 다 차면 아래 내용 실행하지 않음.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->allItems[idx];

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
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
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}

	// 아이템 추가하기
	State = "add";

	if (item->count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->itemIndex = idx;
		item->inventoryIndex = ItemCnt;
		item->count += Num;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->count += Num;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::AddItem3(TSubclassOf<UYJ_Item> ItemClass)
{
	auto Item = ItemClass.GetDefaultObject();
	// 인벤토리 창이 다 차거나 들어오는 Item 이 유효하지 않으면 아래 내용 실행하지 않음.
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
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
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	State = "add";
	Items.Add(Item);
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItem(UYJ_Item* Item)
{
	// 인벤토리 창이 비거나 들어오는 Item 이 유효하지 않으면 아래 내용 실행하지 않음.
	if (Items.Num() <= 0 || !Item)
	{
		return false;
	}

	Item->OwningInventory = nullptr;
	Item->World = nullptr;
	Items[ItemCnt] = nullptr;
	//Items.RemoveSingle(Item);
	State = "remove";
	OnInventoryUpdated.Broadcast();
	return true;
}

// 게임인스턴스의 AllItems 배열에서 Item번째 YJ_Item 을 가져와서 remove
bool UYJ_InventoryComponent::RemoveItem2(EItemEnum Item)
{
	// 인벤토리 창이 비면 아래 내용 실행하지 않음.
	if (ItemCnt <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->allItems[idx];

	// 아이템 지우기
	State = "remove";

	if (item->count <= 1)
	{
		item->OwningInventory = nullptr;
		item->World = nullptr;
		item->itemIndex = idx;
		item->inventoryIndex = -1;
		item->count = 0;
		Items.RemoveSingle(item);
		ItemCnt--;
		UE_LOG(LogTemp, Warning, TEXT("Remove Item"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), Items.Num());
	}
	else
	{
		item->count--;
		UE_LOG(LogTemp, Warning, TEXT("Minus item count"));
	}

	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItemByNumber(EItemEnum Item, int32 Num)
{
	// 인벤토리 창이 비면 아래 내용 실행하지 않음.
	if (ItemCnt <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->allItems[idx];

	if (item->count < Num) return false;

	// 아이템 지우기
	State = "remove";

	if (item->count - Num <= 0)
	{
		item->OwningInventory = nullptr;
		item->World = nullptr;
		item->itemIndex = idx;
		item->inventoryIndex = -1;
		item->count = 0;
		//Items[ItemCnt] = nullptr;
		Items.RemoveSingle(item);
		//Items.SetNum(Capacity);
		ItemCnt--;
		UE_LOG(LogTemp, Warning, TEXT("Remove Item"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), Items.Num());
	}
	else
	{
		//Items[item->InventoryIndex]->Count--;
		item->count -= Num;
		UE_LOG(LogTemp, Warning, TEXT("Minus item count"));
	}
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItem3(TSubclassOf<UYJ_Item> ItemClass)
{
	return false;
}

UYJ_Item* UYJ_InventoryComponent::EnumIndexToItem(EItemEnum Item)
{
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->allItems[idx];
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
	if (Item->inventoryIndex >= 0) return true;
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
	//if (!item) return false;

	//if (item->Count > 0) return true;
	//else return false;
}

bool UYJ_InventoryComponent::AddCash(int32 AddPrice)
{
	if (Cash - AddPrice >= 0)
	{
		Cash = Cash - AddPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::AddAccountBalance(int32 AddPrice)
{
	if (AccountBalance - AddPrice >= 0)
	{
		AccountBalance = AccountBalance - AddPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::UpdateBankBookInterest()
{
	// 통장이 없다면 리턴
	if (BankBook.bHaveBankBook == false) return true;
	// 통장이자 매일 더하고, 7일이 지나면 이자주기
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
	// 만약 갚을 대출금이 없으면 리턴
	if (Loan.bUnpaidLoan == false)
	{
		Loan.LoanPastDate = 0;
		Loan.LoanInterest = 0;
		return true;
	}

	// 대출금을 갚지않았고, 7일이 지났으면 이자가 붙음
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
	// 세금 고지한지 7일 지났으면, 세금율 랜덤으로 세금계산
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
