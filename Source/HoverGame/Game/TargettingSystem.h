// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TargettingSystem.generated.h"

class UTargetComponent;

//Singleton actor that holds all the target components in the map and helps with querying them
// Only one should exist at the same time, DO NOT SPAWN IT.
// The query functions are much faster than normal ue4 querying, they are fine to use everywhere
UCLASS()
class HOVERGAME_API ATargettingSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargettingSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Finds all the TargetComponents in a cone. Does no sorting
	UFUNCTION(BlueprintCallable, Category = Targetting)
		TArray<UTargetComponent*> GetTargetsInCone(FVector Origin, FVector Direction, float AngleRad, float MaxDistance);



	//register target component with system
	void RegisterTarget(UTargetComponent * newTarget);

	//remove target component from array
	void RemoveTarget(UTargetComponent * newTarget);


protected:
	TArray<TWeakObjectPtr<UTargetComponent>> TargetComponents;
};
