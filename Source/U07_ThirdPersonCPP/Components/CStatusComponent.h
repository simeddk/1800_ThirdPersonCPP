#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedType : uint8
{
	Sneak, Walk, Run, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U07_THIRDPERSONCPP_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetSneakSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Run]; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE bool IsCanMove() { return bCanMove; }

	void SetMove();
	void SetStop();
	void ChangeMoveSpeed(EWalkSpeedType InType);

	void DecreaseHealth(float InAmount);
	void IncreaseHealth(float InAmount);
	FORCEINLINE bool IsDead() { return CurrentHealth <= 0; }

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float WalkSpeed[(int32)EWalkSpeedType::Max] = { 200.f, 400.f, 600.f };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.f;

private:
	bool bCanMove = true;
	float CurrentHealth;
		
};
