#include "CBTTaskNode_Change.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/CEnemy.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Change::UCBTTaskNode_Change()
{
	NodeName = "Change";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Change::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACEnemy* enemy = Cast<ACEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(enemy);
	CheckNullResult(actionComp, EBTNodeResult::Failed);

	if (Type == EActionType::Warp)
	{
		if (actionComp->IsWarpMode() == false)
			actionComp->SetWarpMode();
	}
	else if (Type == EActionType::MagicBall)
	{
		if (actionComp->IsMagicBallMode() == false)
			actionComp->SetMagicBallMode();
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Change::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNull(controller);

	ACEnemy* enemy = Cast<ACEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	if (stateComp->IsIdleMode())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


}
