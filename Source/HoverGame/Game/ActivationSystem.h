// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivationSystem.generated.h"

class UActorActivationComponent;

struct FActivationState {
	TWeakObjectPtr<UActorActivationComponent> Component;
	bool bIsActive;
};

UCLASS()
class HOVERGAME_API AActivationSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivationSystem();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//register target component with system
	void RegisterActivationComponent(UActorActivationComponent* newTarget, bool bStartState);

	//remove target component from array
	void RemoveActivationComponent(UActorActivationComponent* newTarget);


protected:
	//Saved Components
	TArray<FActivationState> SavedComponents;
};
