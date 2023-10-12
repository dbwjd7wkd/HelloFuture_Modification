// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minsu_Activate.h" // ���
#include "Minsu_PlantSeed.h" // ���
#include "Minsu_ShakeTree.h" // ���
#include "YJ_SaveGame.h" // save game ����ü ���
#include "Kismet/GameplayStatics.h" // save game ����ü ���
#include "HelloFutureCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSaveGameDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadGameDelegate);

UCLASS(config = Game)
class AHelloFutureCharacter : public ACharacter, public IMinsu_Activate, public IMinsu_PlantSeed, public IMinsu_ShakeTree
{
	GENERATED_BODY()

public:
	AHelloFutureCharacter();
	virtual void BeginPlay() override;

	/** Replicated �� �Ӽ��� ��� */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** save game */
public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void SaveGame();
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void LoadGame();

	UPROPERTY(BlueprintReadOnly, Category = "SaveGame")
		class UYJ_SaveGame* saveGameInstance;
	UPROPERTY(BlueprintReadOnly, Category = "SaveGame")
		class UYJ_SaveGame* loadGameInstance;
	UPROPERTY(BlueprintReadOnly)
		class UYJ_GameInstance* gameInstance;
	UPROPERTY(BlueprintAssignable, Category = "SaveGame")
		FSaveGameDelegate OnSaveGame;
	UPROPERTY(BlueprintAssignable, Category = "SaveGame")
		FLoadGameDelegate OnLoadGame;

	/** Ŀ���� ��������ȭ */
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Custom")
		void BP_GetCustom(const FString& OldName);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Custom")
		void GetCustom_OnServer(const FString& OldName);
		void GetCustom_OnServer_Implementation(const FString& OldName);
		bool GetCustom_OnServer_Validate(const FString& OldName);
	UFUNCTION(Client, Reliable, WithValidation, BlueprintCallable, Category = "Custom")
		void GetCustom_OnClient(const FString& OldName);
		void GetCustom_OnClient_Implementation(const FString& OldName);
		bool GetCustom_OnClient_Validate(const FString& OldName);

	/** �г���_��������ȭ */
public:
	// �г��� ������ (������ �������� ���� ����), ������ ���ٸ� ServerSendName ����
	UFUNCTION(BlueprintCallable, Category = "Name")
		void SetName(const FText& PlayerName);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Name")
		void ServerSetName(const FText& PlayerName);
		void ServerSetName_Implementation(const FText& PlayerName);
		bool ServerSetName_Validate(const FText& PlayerName);
	UFUNCTION(NetMulticast, Reliable, WithValidation, BlueprintCallable, Category = "Name")
		void MulticastSetName(const FText& PlayerName);
		void MulticastSetName_Implementation(const FText& PlayerName);
		bool MulticastSetName_Validate(const FText& PlayerName);
	UFUNCTION(BlueprintCallable, Category = "Name")
		void OnRep_Name();
	UFUNCTION(BlueprintCallable, Category = "Name")
		void UpdateNameTextRender();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Replicated, Category = "Name")
		FString CurrentName; // ���� �� ���̰� ���� ������ ��ü�ϰ� �ִµ�, �ٲٱ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_Name, Category = "Name")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		class UTextRenderComponent* NameTextRender;

	UFUNCTION(BlueprintCallable, Category = "Name")
		void PrintDebug(const FString& str);
	/** inventory */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		class UYJ_InventoryComponent* inventory;

public:
	/** widget manager - ĳ���Ϳ� �ε����� ���� UI ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		class UUserWidget* UI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", Instanced)
		TMap<TSubclassOf<class AActor>, class UUserWidget*> WidgetMap;

	/** �÷��̾� �ð� */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		float time;
	
	/** ���� */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz")
		int32 quizScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz")
		bool isQuiz = false;

///////////////////////// Interactive ////////////////////////////////////////
protected :
	class AOH_InteractiveBase* currentInteractive;
public:
	FORCEINLINE class AOH_InteractiveBase* GetInteractive() {return currentInteractive; }

	void SetInteractiveInRange(class AOH_InteractiveBase* Interactive);
	void ClearInteractiveInRange(class AOH_InteractiveBase* Interactive);

/////////////////////////// ä�� ////////////////////////////////////////
public:
	void Chatting();
	UFUNCTION(BlueprintCallable, Category = "Chat")
		void AttemptToSendChatMessage(const FString& Message);

	// ä�� ������ (������ �������� ���� ����), ������ ���ٸ� ServerSendChatMessage ����
	UFUNCTION(BlueprintCallable, Category = "Chat")
		void SendChatMessage(const FString& Message);
	// ���� �޼��� ����� (ä�� ������ 5�� ��)
	UFUNCTION(BlueprintCallable, Category = "Chat")
		void ClearChatMessage();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Chat")
		void ServerSendChatMessage(const FString& Message);
		void ServerSendChatMessage_Implementation(const FString& Message);
		bool ServerSendChatMessage_Validate(const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Chat")
		void OnRep_CurrentMessage();
	UFUNCTION(BlueprintCallable, Category = "Chat")
		void UpdateChatText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat")
		class UTextRenderComponent* ChatText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, ReplicatedUsing = OnRep_CurrentMessage, Category = Chat)
		FString CurrentMessage;
	UPROPERTY(EditDefaultsOnly, Category = "Chat")
		TSubclassOf<UUserWidget> ChatWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chat")
		class UMinsu_ChatWidget* ChatWidget;

////////////////////////////// �������̽� ��� /////////////////////////////////
public:
	void KeyShakeTree();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Farm")
		void ShakeTree();
		virtual void ShakeTree_Implementation() override;

	// ����Ʈ���̽� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farm")
		float TraceDistance = 500.f;

///////////////////////////////////////////////////////////////////////
// �� ����
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoughtClothes")
		TMap<FString, bool> BoughtClothes;
	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		bool GetBoughtClothes(FString key);
	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		void SetBoughtClothes(FString key, bool value);

	// ���� �� �̸� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PreLevelName")
		FName preLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoughtClothes")
		TArray<FcloseBoughtMStruct> closetBoughts;

	/*
		* Opens a file dialog for the specified data. Leave FileTypes empty to be able to select any files.
		* Filetypes must be in the format of: <File type Description>|*.<actual extension>
		* You can combine multiple extensions by placing ";" between them
		* For example: Text Files|*.txt|Excel files|*.csv|Image Files|*.png;*.jpg;*.bmp will display 3 lines for 3 different type of files.
	*/
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	void OpenFileDialog(int32 frameNumber, const FString & DialogTitle, const FString & DefaultPath, const FString & FileTypes, TArray<FString>&OutFileNames);
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
		UTexture2D* GetFile(const FString& File, bool& IsValid, int32& Width, int32& Height);

/////////////////////////////////////////////////////////////////////
/// ī�޶�, ��ǲ ����
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();
	/** Called for forwards/backward input */
	void MoveForward(float Value);
	/** Called for side to side input */
	void MoveRight(float Value);
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpRate;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
		class UCameraComponent* FollowCamera;

};
