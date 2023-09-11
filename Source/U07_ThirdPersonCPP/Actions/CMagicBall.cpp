#include "CMagicBall.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACMagicBall::ACMagicBall()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Sphere);
	
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.f;

	Projectile->InitialSpeed = 2000.f;
	Projectile->MaxSpeed = 4000.f;
	Projectile->ProjectileGravityScale = 0.f;

}

void ACMagicBall::BeginPlay()
{
	Super::BeginPlay();
	
}

