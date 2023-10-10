#include "CDoAction_Storm.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAttachment.h"

void ACDoAction_Storm::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* child : OwnerCharacter->Children)
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Storm"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(child);
			break;
		}
	}
}

void ACDoAction_Storm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bActivating);

	CurrentYaw += AroundSpeed * DeltaTime;
	if (FMath::IsNearlyEqual(CurrentYaw, 360.f))
		CurrentYaw = 0.f;

	FVector location = OwnerCharacter->GetActorLocation();
	FVector awayFrom = FVector(Radius, 0, 0).RotateAngleAxis(CurrentYaw, OwnerCharacter->GetActorUpVector());

	location += awayFrom;

	Box->SetWorldLocation(location);
}

void ACDoAction_Storm::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());

	CheckTrue(bActivating);
	bActivating = true;

	StateComp->SetActionMode();
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Storm::Begin_DoAction()
{
	Super::Begin_DoAction();

	//OwnerCharacter Forward Vector to Yaw
	CurrentYaw = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;

	//Spawn Particle
	if (!!Datas[0].Effect)
	{
		Particle = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, NAME_None);
		Particle->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
		Particle->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());
	}

	//On Collision
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OnCollisions();

	//DamagePerTime(0.1s) Timer
	UKismetSystemLibrary::K2_SetTimer(this, "TickDamage", 0.1f, true);
}

void ACDoAction_Storm::End_DoAction()
{
	Super::End_DoAction();

	StatusComp->SetMove();
	StateComp->SetIdleMode();

	FTimerDynamicDelegate onEndActiveTime;
	onEndActiveTime.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(onEndActiveTime, ActiveTime, false);
}

void ACDoAction_Storm::Abort()
{
	Super::Abort();

	Finish();
}

void ACDoAction_Storm::OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Storm::OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_Storm::TickDamage()
{
	FDamageEvent damageEvent;

	for (int32 i = 0;  i < HittedCharacters.Num(); i++)
	{
		UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);

		bool bIgnore = false;
		bIgnore |= (stateComp->IsDeadMode());
		bIgnore |= (HittedCharacters[i]->IsPendingKill());
		bIgnore |= (HittedCharacters[i] == nullptr);
		if (bIgnore) continue;

		HittedCharacters[i]->TakeDamage
		(
			Datas[0].Power,
			damageEvent,
			OwnerCharacter->GetController(),
			this
		);
	}
}

void ACDoAction_Storm::Finish()
{
	//Destory Particle
	if (!!Particle)
		Particle->DestroyComponent();

	//Off Collision
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OffCollisions();

	//Clear TickDamage
	UKismetSystemLibrary::K2_ClearTimer(this, "TickDamage");

	//Reset bActivating
	bActivating = false;
}
