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

	FVector handSocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");
	//OwnerCharacter->GetController()->GetPlayerViewPoint(,);
	//Todo. 카메라위치, 카메라회전


	FTransform transmform = Datas[0].EffectTransform;
	transmform.AddToTranslation(handSocketLocation);
	transmform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));

	ACMagicBall* magicBall = GetWorld()->SpawnActorDeferred<ACMagicBall>
		(
			Datas[0].ProjectileClass,
			transmform,
			OwnerCharacter,
			OwnerCharacter,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	//Todo. 뭔가 넣을 것이다.

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
