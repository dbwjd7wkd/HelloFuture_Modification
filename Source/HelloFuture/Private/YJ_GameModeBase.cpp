// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_GameModeBase.h"
#include "HelloFutureCharacter.h"
#include "YJ_InventoryComponent.h"
#include "YJ_WaitingTicketItem.h"

void AYJ_GameModeBase::AddWaitingNumber()
{
	WaitingNumber++;
}

void AYJ_GameModeBase::MinusWaitingNumber()
{
	WaitingNumber--;
}

bool AYJ_GameModeBase::CheckMyOrder(AHelloFutureCharacter* Player)
{
	// 1. ����ִ� ���ǥ ������ ��ȣ�� ���� ���Ӹ���� ���� order�� �´��� Ȯ��
	if (Player)
	{
		for (auto Item : Player->inventory->Items)
		{
			// 2. ���� ��� �������� �ִٸ�
			UYJ_WaitingTicketItem* WaitingTicketItem = Cast<UYJ_WaitingTicketItem>(Item);
			if (WaitingTicketItem)
			{
				// ���� ��� ������ ��ȣ�� ��ȣ�� ������ ���ٸ� true ��ȯ (��ȭ����)
				if (WaitingTicketItem->ItemWaitingNumber == WaitingNumber) return true;
				// ������ �ٸ��ٸ� false ��ȯ
				else return false;
			}
		}

		// 3. ���� ��� �������� ���ٸ� false ��ȯ
		return false;
	}

	return false;
}
