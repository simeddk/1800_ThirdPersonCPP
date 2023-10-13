#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CActionComponent.h"
#include "Components/CFeetComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		EActionType ActionType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "IK")
		FFeetData FeetData;
};
