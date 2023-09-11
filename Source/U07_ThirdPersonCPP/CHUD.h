#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACHUD();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

public:
	FORCEINLINE void EnableAim() { bVisibleAim = true; }
	FORCEINLINE void DisableAim() { bVisibleAim = false; }

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* CrosshairTex;

private:
	class UCStateComponent* StateComp;
	UEnum* StateTypeEnum;

	bool bVisibleAim;
};
