// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor *Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetWorldLocationAndRotation(GetComponentLocation(), GetComponentRotation());
            Component->SetSimulatePhysics(false);
            TriggerOn = true;
        }
    }
    else
    {
        TriggerOn = false;
    }
}
AActor *UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);
    
    for (auto *Actor : Actors)
    {
        UE_LOG(LogTemp, Display, TEXT("Actor %s"), *Actor->GetActorNameOrLabel());
        if (Actor->ActorHasTag(UnlockTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }
    return nullptr;
}
bool UTriggerComponent::IsTriggerOn() const
{
    return TriggerOn;
}