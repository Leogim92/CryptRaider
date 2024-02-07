// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lever.h"
#include "TriggerComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FVector moveOffset{};

	UPROPERTY(EditAnywhere)
	float moveTime{4.0f};

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Locks {};

	TArray<ULever*> Levers{};
	TArray<UTriggerComponent*> Triggers{};

	bool shouldMove {false};

	FVector originalLocation;


	bool CheckLocks() const;
	void Move(const FVector& Start, const FVector& End, float DeltaTime, float Speed);
};
