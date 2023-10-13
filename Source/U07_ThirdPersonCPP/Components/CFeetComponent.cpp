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
	FRotator leftRotation;
	Trace(LeftFootSocket, leftDistance, leftRotation);

	float rightDistance;
	FRotator rightRotation;
	Trace(RightFootSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);

	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	Data.LeftDistance.Y = UKismetMathLibrary::FInterpTo(Data.LeftDistance.Y, (leftDistance - offset), DeltaTime, InterpSpeed);
	Data.RightDistance.Y = UKismetMathLibrary::FInterpTo(Data.RightDistance.Y, (rightDistance - offset), DeltaTime, InterpSpeed);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
}

void UCFeetComponent::Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.f;
	OutRotation = FRotator::ZeroRotator;

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

	//In Air Length
	float undergroundLength = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	OutDistance = AdjustHeight + undergroundLength - AddLength;

	//------------------
	FVector impactNormal = hitResult.ImpactNormal;

	float pitch = -UKismetMathLibrary::DegAtan2(impactNormal.X, impactNormal.Z);
	float roll = UKismetMathLibrary::DegAtan2(impactNormal.Y, impactNormal.Z);
	
	pitch = FMath::Clamp(pitch, -45.f, 45.f);
	roll = FMath::Clamp(roll, -45.f, 45.f);
	
	OutRotation = FRotator(pitch, 0.f, roll);

	//Draw Debug Impact Normal
	DrawDebugDirectionalArrow
	(
		GetWorld(),
		hitResult.ImpactPoint,
		hitResult.ImpactPoint + impactNormal * 100.f,
		3.f,
		FColor::Orange,
		false,
		-1.f,
		0,
		2.f
	);
}

