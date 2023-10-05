#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSelectActionWidget_Icon.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCSelectActionWidget_Icon : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintCallable)
		void OnPressed();

	UFUNCTION(BlueprintCallable)
		void OnHover();

	UFUNCTION(BlueprintCallable)
		void OnUnhover();

private:
	class UCSelectActionWidget_Group* GetParentWidget();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* ImageButton;
};
