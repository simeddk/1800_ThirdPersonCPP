#include "CBTTaskNode_MoveSpeed.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/CEnemy.h"

UCBTTaskNode_MoveSpeed::UCBTTaskNode_MoveSpeed()
{
    NodeName = "MoveSpeed";
}

EBTNodeResult::Type UCBTTaskNode_MoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* controller = OwnerComp.GetAIOwner();
    CheckNullResult(controller, EBTNodeResult::Failed);

    ACEnemy* enemy = Cast<ACEnemy>(controller->GetPawn());
    CheckNullResult(enemy, EBTNodeResult::Failed);

    UCStatusComponent* statusComp = CHelpers::GetComponent<UCStatusComponent>(enemy);
    CheckNullResult(statusComp, EBTNodeResult::Failed);

    statusComp->ChangeMoveSpeed(Type);

    return EBTNodeResult::Succeeded;
}
