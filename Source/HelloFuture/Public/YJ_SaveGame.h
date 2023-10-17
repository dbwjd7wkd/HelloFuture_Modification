// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "YJ_InventoryComponent.h"
#include "YJ_SaveGame.generated.h"

// �� ī�װ� enum
UENUM(BlueprintType)
enum class EClosetBoughtCategory : uint8
{
    Category1 UMETA(DisplayName = "None"),
    Category2 UMETA(DisplayName = "Head"),
    Category3 UMETA(DisplayName = "HairStyle"),
    Category4 UMETA(DisplayName = "Nose"),
    Category5 UMETA(DisplayName = "UpperClothes"),
    Category6 UMETA(DisplayName = "UnderClothes"),
    Category7 UMETA(DisplayName = "WholeClothes"),
    Category8 UMETA(DisplayName = "Glasses"),
    Category9 UMETA(DisplayName = "Hat"),
    Category10 UMETA(DisplayName = "Bag"),
    Category11 UMETA(DisplayName = "Watch"),
    Category12 UMETA(DisplayName = "HatHair"),
    Category13 UMETA(DisplayName = "Hair_Acc_R"),
    Category14 UMETA(DisplayName = "Hair_Acc_BB"),
};

// ������ �� ����ü
USTRUCT(Atomic, BlueprintType)
struct FcloseBoughtMStruct
{
    GENERATED_BODY()

public:
    // �� ���̷�Ż �޽�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        USkeletalMesh* ClosetBoughtMesh;
    // �� ��Ƽ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<UMaterialInterface*> ClosetBoughtMaterial;
    // �� ī�װ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
       EClosetBoughtCategory ClosetBoughtCategory;
};

UCLASS()
class HELLOFUTURE_API UYJ_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UYJ_SaveGame();

    /** save slot ����*/
    // save slot �̸�
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
        FString SaveSlotName;
    // save slot �ε���
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
        int32 UserIndex;

    /** �÷��̾� ���� */
    // �÷��̾� �̸�
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
        FText PlayerName;
    // �÷��̾ ���� ������ �÷��� �� �ð�(����: ��)
    UPROPERTY(VisibleAnywhere, Category = "Basic")
        float Time;

    /** �� ���� */
    // ������ ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoughtClothes")
        TMap<FString, bool> BoughtClothes;
    // ������ �� ������� in ����(Material array)-�ܺ� �迭
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<FcloseBoughtMStruct> ClosetBoughts;

    /** �κ��丮 ���� */
    // �����ܰ�
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
        int32 AccountBalance;
    // ����
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
        int32 Cash;
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 columnLength;
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 rowLength;
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 Capacity;

    /** �κ��丮 ������ ���� */
    // �κ��丮 �� ���� ������ ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        int32 ItemCnt;
    // �κ��丮�� �� ������ �ε���
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> InventoryIdxArray;
    // �κ��丮�� �� ������ ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> InventoryCntArray;

    //UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
    //    TArray<TSubclassOf<class UYJ_Item>> Items;
    // ���� ����
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    TArray<class UYJ_Item*> Items;

    /** �ſ� ���� ���� */
    // ��������
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
        FBankBookStruct BankBook;
    // ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
        FLoanStruct Loan;
    // ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
        FTaxStruct Tax;

    /** ����Ʈ ���� */
    // ����Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
    UActorComponent* SaveQuest;

    /** �帥 �ð� ���� */
	// �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
        int32 WorldTime;
    // ��ü���� �ð� ����ü
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		FDateTime WorldTimeStructure;
};
