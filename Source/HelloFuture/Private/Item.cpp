// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Misc/OutputDeviceNull.h"
#include "UObject/ConstructorHelpers.h"
#include "HelloFutureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	// ĸ���ݸ��� ������Ʈ ���� �� ����
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	Capsule->SetCollisionProfileName(TEXT("Item"));
	//CapsuleCollision->InitCapsuleSize(42.f, 96.0f);
	//CapsuleCollision->SetCollisionProfileName(TEXT("YJ_HelloFutureCharacter_Capsule"));
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &AItem::OnComponentEndOverlap);

	// �޽� ������Ʈ ���� �� ����
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));



	//static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	//if (StaticMeshAsset.Succeeded())
	//{
	//	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	//	StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	//	StaticMesh->SetWorldScale3D(FVector(0.8f));
	//}
	//StaticMesh->SetCollisionProfileName(TEXT("YJ_HelloFutureCharacter_Mesh"));

	// �ִϸ��̼� ��Ÿ�� ��������
	//static auto AnimBlueprintName = TEXT("AnimBlueprint'/Game/Map/Animation/REALMain_ABP.REALMain_ABP_C'");
	//static auto AnimBlueprintFinder = ConstructorHelpers::FClassFinder<UAnimInstance>(AnimBlueprintName);
	//if (AnimBlueprintFinder.Succeeded())
	//{
	//	StaticMesh->SetAnimInstanceClass(AnimBlueprintFinder.Class);
	//}
}

void AItem::OnConstruction(const FTransform& Transform)
{
	StaticMesh->SetStaticMesh(NewMesh);
}

void AItem::Construct()
{
	//StaticMesh->SetStaticMesh(NewMesh);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	// �ε��� �� �÷��̾��̸�, 
	// 0. �÷��̾� �����ϱ�
	Player = Cast<AHelloFutureCharacter>(OtherActor);
	if (!Player)
	{
		Player = nullptr;
		return;
	}

	Player->OnPickUpItemDelegate.BindUObject(this, &AItem::PickUpItem);

}

void AItem::OnComponentEndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ������ �� �÷��̾���, 
	// �÷��̾� nullptr�� �����.
	Player = Cast<AHelloFutureCharacter>(OtherActor);
	if (Player)
	{
		Player->OnPickUpItemDelegate.Unbind();
		Player = nullptr;
	}

}

void AItem::PickUpItem()
{
	if (!Player) return;

	// 1. ������ �ݴ� �ִϸ��̼� + ���� ���. => ĳ������ �������Ʈ �Լ� �θ���
	if (PickingUpMontage)
	{
		FOutputDeviceNull AR;
		const FString command = FString::Printf(TEXT("GrabItemOnServer %s %s"), *PickingUpMontage->GetName(), *this->GetName());
		Player->CallFunctionByNameWithArguments(*command, AR, NULL, true);
	}

	// 2. �κ��丮�� �ֿ� ������ �ֱ�.
	Player->Inventory->AddItem2(EItemEnum::Apple);

	// 3. ���� ������ ��ü ���ֱ�.
	this->Destroy();
}

