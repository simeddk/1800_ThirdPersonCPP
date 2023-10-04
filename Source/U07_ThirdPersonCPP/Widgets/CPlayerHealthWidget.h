#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerHealthWidget.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealth();
	void UpdateHealth_Implementation();

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* CircleGuage;
	
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthText;

	UPROPERTY(meta = (BindWidgetAnim))
		class UWidgetAnimation* DecreaseImpact;

private:
	class UMaterialInstanceDynamic* Material;
	class UCStatusComponent* StatusComp;
};
