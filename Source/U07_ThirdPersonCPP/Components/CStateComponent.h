#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll, BackStep,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChangedSignature, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U07_THIRDPERSONCPP_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public: //Get State
	UFUNCTION(BlueprintPure)
		bool IsIdleMode() { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		bool IsRollMode() { return Type == EStateType::Roll; }

	UFUNCTION(BlueprintPure)
		bool IsBackStepMode() { return Type == EStateType::BackStep; }

public: //Set State
	void SetIdleMode();
	void SetRollMode();
	void SetBackStepMode();

private: 
	void ChangeType(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;

};
