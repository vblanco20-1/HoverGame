// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivationSystem.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorActivationComponent.h"

// Sets default values
AActivationSystem::AActivationSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AActivationSystem::Tick(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ActivationSystem);
	Super::Tick(DeltaTime);

	SavedComponents.RemoveAllSwap([=](FActivationState& State) -> bool {

		return !State.Component.IsValid();
		}
	, false);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC && PC->GetPawn()){
	
		APawn* PlayerPawn = PC->GetPawn();
		
		const FVector PlayerLoc = PlayerPawn->GetActorLocation();

		for (auto &State : SavedComponents)
		{			
			UActorActivationComponent* ActivComp = State.Component.Get();


			if (ActivComp->bActivateByDistance)
			{
				const FVector Loc = ActivComp->GetOwner()->GetActorLocation();
				bool bIsNear = FVector::Dist(PlayerLoc, Loc) < ActivComp->ActivationDistance;

				if (bIsNear && !State.bIsActive)
				{
					ActivComp->PlayerEntered.Broadcast(PlayerPawn);
					State.bIsActive = true;
				}
				else if (!bIsNear && State.bIsActive) {
					ActivComp->PlayerExited.Broadcast(PlayerPawn);
					State.bIsActive = false;
				}

			}			
		}
	}
}

void AActivationSystem::RegisterActivationComponent(UActorActivationComponent* newTarget, bool bStartingState)
{
	if (newTarget)
	{
		FActivationState State;

		State.Component = newTarget;
		State.bIsActive = bStartingState;
		
		SavedComponents.Add(State);
	}
}

void AActivationSystem::RemoveActivationComponent(UActorActivationComponent* newTarget)
{
	if (newTarget)
	{	
		
		SavedComponents.RemoveAllSwap([=](FActivationState& State) -> bool {
			
			return State.Component == newTarget;
		}
		,false);
	}
}

