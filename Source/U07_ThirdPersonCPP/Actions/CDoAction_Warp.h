#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator);
	bool IsPlayerControlled();

private:
	class UStaticMeshComponent* WarpPoint;
	FVector WarpLocation;
};
