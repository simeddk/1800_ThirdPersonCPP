#include "CDoAction_Storm.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Storm::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* child : OwnerCharacter->Children)
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Storm"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(child);
			break;
		}
	}
}

void ACDoAction_Storm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACDoAction_Storm::DoAction()
{
	Super::DoAction();

	StateComp->SetActionMode();
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Storm::Begin_DoAction()
{
	Super::Begin_DoAction();

	UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, NAME_None);
	//Todo. 파티클 위치 잡아주기
}

void ACDoAction_Storm::End_DoAction()
{
	Super::End_DoAction();
}

void ACDoAction_Storm::Abort()
{
	Super::Abort();
}
