#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

private:
	class UCStateComponent* StateComp;
	UEnum* StateTypeEnum;
};
