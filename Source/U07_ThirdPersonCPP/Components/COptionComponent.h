#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U07_THIRDPERSONCPP_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetHorizontalSpeed() { return HorizontalSpeed; }
	FORCEINLINE float GetVerticalSpeed() { return VerticalSpeed; }
	
	FORCEINLINE float GetZoomSpeed() { return ZoomSpeed; }
	FORCEINLINE float GetZoomMin() { return ZoomRange.X; }
	FORCEINLINE float GetZoomMax() { return ZoomRange.Y; }

private:
	UPROPERTY(EditAnywhere, Category = "Mouse")
		float HorizontalSpeed = 45.f;

	UPROPERTY(EditAnywhere, Category = "Mouse")
		float VerticalSpeed = 45.f;
	
	UPROPERTY(EditAnywhere, Category = "Mouse")
		float ZoomSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Mouse")
		FVector2D ZoomRange = FVector2D(100, 1000);
};
