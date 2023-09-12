// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_GameInstance.h"
#include "YJ_Item.h"
#include "SocketSubsystem.h"
//#include "YJ_InventoryComponent.h"

UYJ_GameInstance::UYJ_GameInstance()
{
    int length = 13;
    for (int i=0; i < length; i++)
    {
        int x = 100;
        int y = -750 + 100 * i;
        int z = 100;
        closetSpawnLocation.Add(FVector(x,y,z));
    }
    
}

// ������ �迭���� �����ؼ� ��������
UYJ_Item* UYJ_GameInstance::GetItemAsEnum(EItemEnum itemEnum)
{
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	int32 idx = (int32)itemEnum;
	UYJ_Item* item = gameInstance->allItems[idx];

    return item;
}

// ���� �÷��̾� ��ǻ�� �ּ� ��������
FString UYJ_GameInstance::GetMyIpAddress()
{
    FString IpAddr("NONE");
    bool canBind = false;
    TSharedRef<FInternetAddr> LocalIp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);
    if (LocalIp->IsValid())
    {
        IpAddr = LocalIp->ToString(false);
    }
    return IpAddr;
}
