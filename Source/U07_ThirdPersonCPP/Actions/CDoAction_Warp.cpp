#include "CDoAction_Warp.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay(); 
}

void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	//Todo. DA에서 DoActionClass를 잘못 넣었었군
	//PrintLine();

	CheckFalse(StateComp->IsIdleMode());

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

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}
