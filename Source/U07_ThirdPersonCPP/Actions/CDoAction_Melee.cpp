#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	//액션(공격) 몽타쥬 재생(첫타)
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	//노티파이비긴(콤보 : 넥스트 콤보, 매직볼 : 스폰 프로젝타일.....)
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	//노티파이엔디(아이들 상태, 캔무브 풀어주고...)
}
