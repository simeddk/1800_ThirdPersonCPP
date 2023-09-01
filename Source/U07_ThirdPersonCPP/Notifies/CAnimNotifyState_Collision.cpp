#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData* currData = actionComp->GetCurrentData();
	CheckNull(currData);

	ACAttachment* attachment = currData->GetAttachment();
	CheckNull(attachment);

	attachment->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData* currData = actionComp->GetCurrentData();
	CheckNull(currData);

	ACAttachment* attachment = currData->GetAttachment();
	CheckNull(attachment);

	attachment->OffCollisions();
}
