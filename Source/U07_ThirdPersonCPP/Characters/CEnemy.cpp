#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CStatusComponent.h"
#include "Widgets/CNameWidget.h"
#include "Widgets/CHealthWidget.h"

ACEnemy::ACEnemy()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidget, "HealthWidget", GetMesh());

	//Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");

	//Component Settings
	// -> MeshComp
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/Character/ZLorp/Mesh/ZLorp");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass(&animInstanceClass, "/Game/Enemies/ABP_CEnemy");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	// -> MovementComp
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();

	// -> WidgetComp
	TSubclassOf<UCNameWidget> nameWidgetClass;
	CHelpers::GetClass(&nameWidgetClass, "/Game/Widgets/WB_Name");
	NameWidget->SetWidgetClass(nameWidgetClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 220));
	NameWidget->SetDrawSize(FVector2D(240, 50));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCHealthWidget> healthWidgetClass;
	CHelpers::GetClass(&healthWidgetClass, "/Game/Widgets/WB_Health");
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 180));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	//Create Dynamic Material
	LowerMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	UpperMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);
	GetMesh()->SetMaterial(0, LowerMaterial);
	GetMesh()->SetMaterial(1, UpperMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	Super::BeginPlay();

	//Widget Settings
	NameWidget->InitWidget();
	UCNameWidget* nameWidget = Cast<UCNameWidget>(NameWidget->GetUserWidgetObject());
	if (!!nameWidget)
	{
		nameWidget->SetNames(GetController()->GetName(), GetName());
	}

	HealthWidget->InitWidget();
	UCHealthWidget* healthWidget = Cast<UCHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();
		return;
	}

	State->SetHittedMode();

	return DamageValue;
}

void ACEnemy::ChangeBodyColor(FLinearColor InColor)
{
	LowerMaterial->SetVectorParameterValue("Emissive", InColor);
	UpperMaterial->SetVectorParameterValue("Emissive", InColor);
}
//Todo. 414141.....
void ACEnemy::Hitted()
{
	CLog::Print("¸ÂÀ½");
}

void ACEnemy::Dead()
{
	CLog::Print("²¥¾Ç!!!!");
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted:	Hitted();	break;
		case EStateType::Dead:		Dead();		break;
	}
}
