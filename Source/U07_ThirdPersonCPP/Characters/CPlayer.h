#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "ICharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void ChangeBodyColor(FLinearColor InColor);
	virtual FGenericTeamId GetGenericTeamId() const override;
	FORCEINLINE class UCSelectActionWidget_Group* GetSelectActionWidget() { return SelectActionWidget; }

private: //Axis Event
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);

private: //Action Event
	void OnWalk();
	void OffWalk();
	void OnEvade();
	
	UFUNCTION() void OnFist();
	UFUNCTION() void OnOneHand();
	UFUNCTION() void OnTwoHand();
	UFUNCTION() void OnMagicBall();
	UFUNCTION() void OnWarp();
	UFUNCTION() void OnStorm();

	void OnAction();
	void OnAim();
	void OffAim();

	void OnSelectAction();
	void OffSelectAction();

private:
	void Begin_Roll();
	void Begin_BackStep();

	void Hitted();
	void Dead();
	
	UFUNCTION()
		void End_Dead();
	
public:
	void End_Roll();
	void End_BackStep();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);


private: //Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: //Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 PlayerTeamID = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCPlayerHealthWidget> HealthWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCSelectActionWidget_Group> SelectActionWidgetClass;

private:
	class UMaterialInstanceDynamic* BodyMaterial;

	FGenericTeamId TeamGeneicID;

	float DamageValue;
	class ACharacter* Attacker;
	class AActor* Causer;

	class UCPlayerHealthWidget* HealthWidget;
	class UCSelectActionWidget_Group* SelectActionWidget;
};
