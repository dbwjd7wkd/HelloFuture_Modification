// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_GameInstance.h"
#include "YJ_Item.h"
#include "SocketSubsystem.h"

UYJ_GameInstance::UYJ_GameInstance()
{
    // ClothingShopMap���� ������ ���� ��ġ�� ��ġ ���� �迭�� �߰�
    int32 Length = 13;
    for (int32 i = 0; i < Length; i++)
    {
        int32 X = 100;
        int32 Y = -750 + 100 * i;
        int32 Z = 100;
        closetSpawnLocation.Add(FVector(X, Y, Z));
    }
    
}

UYJ_Item* UYJ_GameInstance::GetItemAsEnum(EItemEnum ItemEnum)
{
    // �����ν��Ͻ� ��������
	UWorld* World = GetWorld();
	if (!World) return false;
	UYJ_GameInstance* GameInstance = Cast<UYJ_GameInstance>(World->GetGameInstance());
	if (!GameInstance) return false;

    // ������ �迭���� enum�� �ε����� �����ؼ� ��������
	int32 ItemIdx = (int32)ItemEnum;
	UYJ_Item* Item = GameInstance->allItems[ItemIdx];

    return Item;
}

FString UYJ_GameInstance::GetMyIpAddress()
{
    // �����ּ� string���� ��ȯ
    FString IpAddr("NONE");
    bool bCanBind = false;
    TSharedRef<FInternetAddr> LocalIp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBind);
    if (LocalIp->IsValid())
    {
        IpAddr = LocalIp->ToString(false);
    }
    return IpAddr;
}
