// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorActivationComponent.h"
#include "Game/HoverGameStatics.h"
#include "Game/ActivationSystem.h"

// Sets default values for this component's properties
UActorActivationComponent::UActorActivationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UActorActivationComponent::BeginPlay()
{
	Super::BeginPlay();

	UHoverGameStatics::FindActivationSystem(GetWorld())->RegisterActivationComponent(this, false);
	// ...
	
	
}

void UActorActivationComponent::BeginDestroy()
{
	Super::BeginDestroy();
	//UHoverGameStatics::FindActivationSystem(GetWorld())->RemoveActivationComponent(this);
}

