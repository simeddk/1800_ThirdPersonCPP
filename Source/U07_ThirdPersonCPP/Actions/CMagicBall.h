#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagicBall.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMagicBall();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		FTransform ImpactTransform;
};
