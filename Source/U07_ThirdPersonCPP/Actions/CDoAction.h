#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CDoAction.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }

	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	virtual void OnAim() {}
	virtual void OffAim() {}

public:
	UFUNCTION()
		virtual void OnBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {}

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* StatusComp;

protected:
	TArray<FDoActionData> Datas;

};
