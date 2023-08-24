#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(ownerPawn);
	CheckNull(actionComp);

	actionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	Speed = ownerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(ownerPawn->GetVelocity(), ownerPawn->GetControlRotation());
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

