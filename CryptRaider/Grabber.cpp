// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle != nullptr && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::AttemptGrab()
{
	FHitResult HitResult{};
	if (TryGetGrabbable(HitResult))
	{
		if (HitResult.GetActor()->ActorHasTag("Statue"))
		{
			GrabObject(&HitResult);
		}
		else if (HitResult.GetActor()->ActorHasTag("Lever"))
		{
			GrabLever(&HitResult);
		}
	}
}
bool UGrabber::TryGetGrabbable(FHitResult &OutHitResult) const
{
	FVector Start{GetComponentLocation()};
	FVector End{Start + GetForwardVector() * MaxGrabDistance};
	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(GrabRadius));
}
void UGrabber::GrabObject(FHitResult *HitResult) const
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	HitResult->GetActor()->Tags.Add("Grabbed");
	UPrimitiveComponent *HitComponent = HitResult->GetComponent();
	HitComponent->WakeAllRigidBodies();
	PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult->ImpactPoint, HitComponent->GetComponentRotation());
	PhysicsHandle->GetGrabbedComponent()->SetSimulatePhysics(true);
}
void UGrabber::GrabLever(FHitResult *HitResult) const
{
	ULever *Lever = HitResult->GetActor()->FindComponentByClass<ULever>();
	if (Lever != nullptr)
	{
		Lever->ToggleLever();
	}
}
void UGrabber::ReleaseComponent()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	UPrimitiveComponent *GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		GrabbedComponent->WakeAllRigidBodies();
		GrabbedComponent->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}
UPhysicsHandleComponent *UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}