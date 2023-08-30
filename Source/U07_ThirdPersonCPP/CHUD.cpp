#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	//playerCharacter->ActionComp->Type => FString => Print
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(playerCharacter);

	StateComp = CHelpers::GetComponent<UCStateComponent>(playerCharacter);

	StateTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStateType"), true);
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	//Print Player StateType
	CheckNull(StateComp);
	CheckNull(StateTypeEnum);

	FString typeStr = StateTypeEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 1.5f);
}