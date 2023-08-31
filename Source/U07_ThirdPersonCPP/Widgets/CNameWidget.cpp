#include "CNameWidget.h"
#include "Components/TextBlock.h"

void UCNameWidget::SetNames_Implementation(const FString& InControllerName, const FString& InPawnName)
{
	ControllerName->SetText(FText::FromString(InControllerName));
	PawnName->SetText(FText::FromString(InPawnName));
}