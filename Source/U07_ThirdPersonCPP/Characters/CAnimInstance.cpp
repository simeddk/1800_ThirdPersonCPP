#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	Speed = ownerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(ownerPawn->GetVelocity(), ownerPawn->GetControlRotation());
}

