// Fill out your copyright notice in the Description page of Project Settings.

#include "Lever.h"

// Sets default values for this component's properties
ULever::ULever()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULever::BeginPlay()
{
	Super::BeginPlay();

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
}

// Called every frame
void ULever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float CurrentPitch = CurrentRotation.Pitch;
	float TargetPitch {};
	if (LeverOn)
	{
		TargetPitch = ActivateRotation.Pitch;
	}
	else
	{
		TargetPitch = DeactivateRotation.Pitch;
	}
	float NewPitch = FMath::FInterpConstantTo(CurrentPitch, TargetPitch, DeltaTime, RotationSpeed);
	FRotator newRotation = FRotator(NewPitch, ActivateRotation.Yaw, ActivateRotation.Roll);
	GetOwner()->SetActorRotation(newRotation);
}

void ULever::ToggleLever()
{
	LeverOn = !LeverOn;
}
bool ULever::IsLeverOn() const
{
	return LeverOn;
}
