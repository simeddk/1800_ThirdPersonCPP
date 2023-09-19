#include "CBehaviorComponent.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CPlayer.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	
}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetTypeFromBB() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetTypeFromBB() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetTypeFromBB() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetTypeFromBB() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return GetTypeFromBB() == EBehaviorType::Hitted;
}

bool UCBehaviorComponent::IsAvoidMode()
{
	return GetTypeFromBB() == EBehaviorType::Avoid;
}

EBehaviorType UCBehaviorComponent::GetTypeFromBB()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

void UCBehaviorComponent::SetAvoidMode()
{
	ChangeType(EBehaviorType::Avoid);
}

ACPlayer* UCBehaviorComponent::GetPlayerKey()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector UCBehaviorComponent::GetLocationKey()
{
	return Blackboard->GetValueAsVector(LocationKey);
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	EBehaviorType prev = GetTypeFromBB();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InNewType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(prev, InNewType);
}

