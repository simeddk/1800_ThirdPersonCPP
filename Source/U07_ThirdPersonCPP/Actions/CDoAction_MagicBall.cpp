#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	CheckFalse(StateComp->IsIdleMode());

	StateComp->SetActionMode();

	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_MagicBall::Begin_DoAction()
{
	//Todo. Spawn Projectile
}

void ACDoAction_MagicBall::End_DoAction()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}
