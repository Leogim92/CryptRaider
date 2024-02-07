// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lever.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API ULever : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULever();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:


	UPROPERTY(EditAnywhere)
	FRotator ActivateRotation;

	UPROPERTY(EditAnywhere)
	FRotator DeactivateRotation;

	UPROPERTY(EditAnywhere)
	float RotationSpeed {20};

	UPROPERTY(EditAnywhere)
	bool LeverOn;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleLever();

	UFUNCTION(BlueprintCallable)
	bool IsLeverOn() const;

};
