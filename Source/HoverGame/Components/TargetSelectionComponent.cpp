// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetSelectionComponent.h"

#include "Game/HoverGameStatics.h"
#include "Game/TargettingSystem.h"
#include "Components/TargetComponent.h"
#include "Player/TargetReticle.h"
// Sets default values for this component's properties
UTargetSelectionComponent::UTargetSelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	TargetCooldown = 0.5f;
	MaxTargets = 4;
	TargettingAngleDegrees = 20.f;
	TargettingMaxDistance = 20000.f;
	// ...
}


// Called when the game starts
void UTargetSelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




void UTargetSelectionComponent::UpdateTargetting(FTransform Aim,float DeltaTime, bool bSelectTargets)
{
	TimeToTarget -= DeltaTime;

	if (TimeToTarget < 0 && bSelectTargets)
	{
		TimeToTarget = TargetCooldown;


		if (SelectedTargets.Num() < MaxTargets)
		{
			auto* TargetSystem = UHoverGameStatics::FindTargettingSystem(this);
			if (TargetSystem)
			{
				//find all target points in a cone
				TArray<UTargetComponent*> PossibleTargets = TargetSystem->GetTargetsInCone(Aim.GetLocation(), Aim.GetRotation().GetForwardVector(), 
																					FMath::DegreesToRadians(TargettingAngleDegrees), TargettingMaxDistance);

				//-----------------------------------------------------------------------
				//Sort predicates for experimenting. Final would be a mix of both.
				//----------------------------------------------------------------------

				//sorts by pure distance
				auto DistanceSortPredicate = [&](UTargetComponent& A, UTargetComponent& B) {

					const float DistA = FVector::DistSquared(Aim.GetLocation(), A.GetComponentLocation());
					const float DistB = FVector::DistSquared(Aim.GetLocation(), B.GetComponentLocation());

					return DistA < DistB;
				};

				//sorts by angle 
				auto AngleSortPredicate = [&](UTargetComponent& A, UTargetComponent& B) {


					FVector ToA = A.GetComponentLocation() - Aim.GetLocation();
					FVector ToB = A.GetComponentLocation() - Aim.GetLocation();
					ToA.Normalize();
					ToB.Normalize();

					FVector Forward = Aim.GetRotation().GetForwardVector();

					float AngleToA = FMath::Acos(FVector::DotProduct(Forward, ToA));
					float AngleToB = FMath::Acos(FVector::DotProduct(Forward, ToA));

					//const float DistA = FVector::DistSquared(Aim.GetLocation(), A.GetComponentLocation());
					//const float DistB = FVector::DistSquared(Aim.GetLocation(), B.GetComponentLocation());

					return AngleToA < 	AngleToB;
				};

				//sort by angle, could check distance too
				PossibleTargets.Sort(AngleSortPredicate);

				
				//find the first target point that is valid and not in the array, and add it to the list, in order
				for (auto t : PossibleTargets)
				{
					if (!SelectedTargets.Contains(t))
					{
						SelectedTargets.AddUnique(t);

						if (TargetReticleClass)
						{
							
							//spawn target reticle
							FActorSpawnParameters SpawnParams;
							ATargetReticle * Reticle = GetWorld()->SpawnActor<ATargetReticle>(TargetReticleClass, t->GetComponentLocation(),t->GetComponentRotation(), SpawnParams);
							if (Reticle)
							{
								Reticle->AttachTarget = t;
								return;
							}							
						}
					}
				}
			}
		}
	}
}

