#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipment.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

	//Todo
	//Equip() -> [1][2][3] -> DrawMontage
	//Begin_Equo...End...

};
