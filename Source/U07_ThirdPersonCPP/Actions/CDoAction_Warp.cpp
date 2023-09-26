#include "CDoAction_Warp.h"
#include "Global.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CBehaviorComponent.h"
#include "CAttachment.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* child : OwnerCharacter->Children)
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Warp"))
		{
			WarpPoint = CHelpers::GetComponent<UStaticMeshComponent>(child);
			break;
		}
	}
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(IsPlayerControlled());
	CheckFalse(*bEquippedThis);

	FVector location;
	FRotator rotation;
	if (GetCursorLocationAndRotation(location, rotation))
	{
		WarpPoint->SetVisibility(true);

		WarpPoint->SetWorldLocation(location + WarpPoint->GetUpVector() * 120.f);
		WarpPoint->SetWorldRotation(rotation);

	}
	else
	{
		WarpPoint->SetVisibility(false);
	}
}

void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());

	if (IsPlayerControlled())
	{
		FRotator temp;
		CheckFalse(GetCursorLocationAndRotation(WarpLocation, temp));
	}
	else
	{
		AAIController* controller = OwnerCharacter->GetController<AAIController>();
		if (!!controller)
		{
			UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
			if (!!behaviorComp)
			{
				WarpLocation = behaviorComp->GetLocationKey();
			}
		}
		
	}

	WarpLocation.Z += OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	StateComp->SetActionMode();
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Warp::Begin_DoAction()
{
	Super::Begin_DoAction();

	FTransform transform = Datas[0].EffectTransform;

	UGameplayStatics::SpawnEmitterAttached
	(
		Datas[0].Effect,
		OwnerCharacter->GetMesh(),
		"Root",
		transform.GetLocation(),
		FRotator(transform.GetRotation()),
		transform.GetScale3D()
	);
}

void ACDoAction_Warp::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->SetActorLocation(WarpLocation);

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNullResult(controller, false);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	
	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objectTypes, true, hitResult))
	{
		OutLocation = hitResult.Location;

		FVector normal = hitResult.ImpactNormal;
		float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);
		float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);

		OutRotator = FRotator(pitch, 0, roll);

		return true;
	}

	return false;
}

bool ACDoAction_Warp::IsPlayerControlled()
{
	return (OwnerCharacter->GetController()->GetClass() == APlayerController::StaticClass());
}
