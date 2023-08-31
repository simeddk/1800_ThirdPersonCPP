#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthWidget.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealth(float InCurrentHealth, float InMaxHealth);
	void UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth);


private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	
};
