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

	//Set Images to IconWidget ImageButton
	for (int32 i = 0; i < IconWidgets.Num(); i++)
	{
		FString key = "Icon";
		key.Append(FString::FromInt(i + 1));

		IconWidgets[key]->SetTextureToImageButton(Images[i]);
	}
}

void UCSelectActionWidget_Group::Pressed(FString InName)
{
	if (IconWidgets[InName]->OnImageButtonPressed.IsBound())
		IconWidgets[InName]->OnImageButtonPressed.Broadcast();

	SetVisibility(ESlateVisibility::Hidden);

	APlayerController* controller = Cast<APlayerController>(GetOwningPlayer());
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(FInputModeGameOnly());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
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
