#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
};
