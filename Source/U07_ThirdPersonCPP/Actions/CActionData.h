#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

//-----------------------------------------------------------------------------
//Struct - EqupmentData
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

//-----------------------------------------------------------------------------
//Struct - DoActionData
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 1.f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;
};

//-----------------------------------------------------------------------------
//Class - DataAsset
//-----------------------------------------------------------------------------
UCLASS()
class U07_THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

public:
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }

private:
	FString GetCustomActorLabel(class ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	UPROPERTY(EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;

private:
	class ACEquipment* Equipment;
	class ACAttachment* Attachment;
	class ACDoAction* DoAction;
};
