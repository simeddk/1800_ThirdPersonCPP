#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CStatusComponent.h"
#include "CBTTaskNode_MoveSpeed.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCBTTaskNode_MoveSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_MoveSpeed();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
		EWalkSpeedType Type;
};
