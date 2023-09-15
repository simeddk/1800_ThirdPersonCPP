#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	
};
