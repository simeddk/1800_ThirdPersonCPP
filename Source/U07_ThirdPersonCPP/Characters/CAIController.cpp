#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	//Todo. (1)Run BT, (2)PerceptionComp
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	// -> PostInitialzie().....
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
