#include "CSelectActionWidget_Group.h"
#include "Global.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include "CSelectActionWidget_Icon.h"

void UCSelectActionWidget_Group::NativeConstruct()
{
	Super::NativeConstruct();

	//Add Item Wiget to Map(with string key)
	CheckNull(Grid);
	TArray<UWidget*> children = Grid->GetAllChildren();
	for (const auto& child : children)
	{
		UCSelectActionWidget_Icon* iconWidget = Cast<UCSelectActionWidget_Icon>(child);
		if (!!iconWidget)
			IconWidgets.Add(child->GetName(), iconWidget);
	}

}

void UCSelectActionWidget_Group::Pressed(FString InName)
{
	CLog::Print(InName + " is Pressed");
}

void UCSelectActionWidget_Group::Hover(FString InName)
{
	UBorder* border = Cast<UBorder>(IconWidgets[InName]->GetWidgetFromName("MyBorder"));
	CheckNull(border);

	border->SetBrushColor(FLinearColor::Red);
}

void UCSelectActionWidget_Group::Unhover(FString InName)
{
	UBorder* border = Cast<UBorder>(IconWidgets[InName]->GetWidgetFromName("MyBorder"));
	CheckNull(border);

	border->SetBrushColor(FLinearColor::White);
}
