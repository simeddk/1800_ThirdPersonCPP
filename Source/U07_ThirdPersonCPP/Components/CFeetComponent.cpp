#include "CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	Trace(LeftFootSocket, leftDistance);

	float rightDistance;
	Trace(RightFootSocket, rightDistance);

	float offset = FMath::Min(leftDistance, rightDistance);

	//Todo.
	//Data.LeftDistance.Y = UKismetMathLibrary::FInterpTo(,);
}

void UCFeetComponent::Trace(FName InSocketName, float& OutDistance)
{
	OutDistance = 0.f;

	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	FVector start = FVector(socketLocation.X, socketLocation.Y, OwnerCharacter->GetActorLocation().Z);
	FVector end = FVector(start.X, start.Y, start.Z - CapsuleHalfHeight - AddLength);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ignoreActors,
		DrawDebugType,
		hitResult,
		false,
		FLinearColor::Green,
		FLinearColor::Red
	);

	CheckFalse(hitResult.IsValidBlockingHit());

	//라인이 땅속으로 파고든 깊이
	float undergroundLength = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();

	//발이 공중에 뜬 길이(떠있으면 음수값), 지면에 닿아 있으면 0
	OutDistance = AdjustHeight + undergroundLength - AddLength;
}

