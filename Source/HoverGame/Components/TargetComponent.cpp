// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetComponent.h"
#include "Game/HoverGameStatics.h"
#include "HoverGame.h"
#include "Game/TargettingSystem.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	//no ticking
	PrimaryComponentTick.bCanEverTick = false;

	bAutoActivate = true;
	// ...
}



// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}

void UTargetComponent::Activate(bool bReset /*= false*/)
{
	Super::Activate(bReset);
	auto sys = UHoverGameStatics::FindTargettingSystem(this);
	if (sys)
	{
		if(bLogRegistering){
		TRACE("Registering target component %s", *GetName());
		}
		
		sys->RegisterTarget(this);
	}
}

void UTargetComponent::Deactivate()
{
	Super::Deactivate();
	auto sys = UHoverGameStatics::FindTargettingSystem(this);
	if (sys)
	{
		if (bLogRegistering) {
			TRACE("Removing target component %s", *GetName());
		}
		sys->RemoveTarget(this);
	}
}

