// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = GetOwner()->GetActorLocation();

	for (auto &lock : Locks)
	{
		ULever *lever = lock->FindComponentByClass<ULever>();
		if (lever != nullptr)
		{
			Levers.Add(lever);
			continue;
		}
		UTriggerComponent *trigger = lock->FindComponentByClass<UTriggerComponent>();
		if (trigger != nullptr)
		{
			Triggers.Add(trigger);
		}
	}
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector currentLocation = GetOwner()->GetActorLocation();
	FVector targetLocation = originalLocation + moveOffset;

	shouldMove = CheckLocks();

	if (shouldMove)
	{
		float Speed = FVector::Distance(originalLocation, targetLocation) / moveTime;
		Move(currentLocation, targetLocation, DeltaTime, Speed);
	}
	else
	{
		float Speed = FVector::Distance(targetLocation, originalLocation) / moveTime;
		Move(currentLocation, originalLocation, DeltaTime, Speed);
	}
}

void UMover::Move(const FVector &Start, const FVector &End, float DeltaTime, float Speed)
{
	FVector newLocation = FMath::VInterpConstantTo(Start, End, DeltaTime, Speed);
	GetOwner()->SetActorLocation(newLocation);
}

bool UMover::CheckLocks() const
{
	for (auto &lever : Levers)
	{
		if (!lever->IsLeverOn())
		{
			return false;
		}
	}
	for (auto &trigger : Triggers)
	{
		if(!trigger->IsTriggerOn())
		{
			return false;
		}
	}
	return true;
}
