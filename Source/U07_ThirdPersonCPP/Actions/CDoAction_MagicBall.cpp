#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CMagicBall.h"
#include "CAim.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);

	ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_MagicBall::AbortByTypeChanged);
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	CheckFalse(Datas.Num() > 0);

	if (Aim->IsAvailable())
		CheckFalse(Aim->IsZooming());

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_MagicBall::Begin_DoAction()
{
	CheckNull(Datas[0].ProjectileClass);

	FVector location;
	FRotator rotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(location, rotation);

	FVector handSocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");
	FVector cameraDirection = rotation.Vector();
	location += cameraDirection * ((handSocketLocation - location) | cameraDirection);

	FTransform transmform = Datas[0].EffectTransform;
	transmform.AddToTranslation(location);
	transmform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));

	ACMagicBall* magicBall = GetWorld()->SpawnActorDeferred<ACMagicBall>
		(
			Datas[0].ProjectileClass,
			transmform,
			OwnerCharacter,
			OwnerCharacter,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	magicBall->OnBeginOverlap.AddDynamic(this, &ACDoAction_MagicBall::OnMagicBallBeginOverlap);
	magicBall->FinishSpawning(transmform);

}

void ACDoAction_MagicBall::End_DoAction()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_MagicBall::OnAim()
{
	CheckNull(Aim);

	Aim->On();
}

void ACDoAction_MagicBall::OffAim()
{
	CheckNull(Aim);

	Aim->Off();
}

void ACDoAction_MagicBall::OnMagicBallBeginOverlap(FHitResult hitResult)
{
	FDamageEvent damageEvent;
	hitResult.Actor->TakeDamage
	(
		Datas[0].Power,
		damageEvent,
		OwnerCharacter->GetController(),
		this
	);
}

void ACDoAction_MagicBall::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());
	Aim->Off();
}
