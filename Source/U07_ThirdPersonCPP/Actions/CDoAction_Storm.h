#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Storm.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACDoAction_Storm : public ACDoAction
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
	virtual void Abort() override;

private:
	UPROPERTY(EditDefaultsOnly)
		float DamagePerTime = 0.1f;

	UPROPERTY(EditDefaultsOnly)
		float ActiveTime = 5.f;

	UPROPERTY(EditDefaultsOnly)
		float AroundSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly)
		float Radius = 150.f;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

private:
	class UBoxComponent* Box;

};
