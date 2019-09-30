// Fill out your copyright notice in the Description page of Project Settings.

#include "TargettingSystem.h"
#include "Components/TargetComponent.h"

// Sets default values
ATargettingSystem::ATargettingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargettingSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargettingSystem::Tick(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("ATargettingSystem::Tick"));
	Super::Tick(DeltaTime);

}

TArray<UTargetComponent*> ATargettingSystem::GetTargetsInCone(FVector Origin, FVector Direction, float AngleRad, float MaxDistance)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("ATargettingSystem::GetTargetsInCone"));
	TArray<UTargetComponent*> Array;

	UWorld* World = GetWorld();
	Direction.Normalize();
	//iterate components
	for (auto T : TargetComponents)
	{
		
		if (T.IsValid())
		{		

			const float Dist = FVector::Dist(T->GetComponentLocation(), Origin);

			//cull by radius
			if (Dist < MaxDistance)
			{
				FVector OriginToTarget = T->GetComponentLocation() - Origin;
				OriginToTarget.Normalize();

				float angle = FMath::Acos(FVector::DotProduct(Direction, OriginToTarget));

				//cull by angle
				if (FMath::Abs(angle) < AngleRad)
				{
					Array.Add(T.Get());
				}
			}
		}
		else
		{
			continue;
		}
	}

	return Array;
}

void ATargettingSystem::RegisterTarget(UTargetComponent * newTarget)
{
	if (newTarget)
	{
		TWeakObjectPtr<UTargetComponent> TargetPointer{ newTarget };
		TargetComponents.AddUnique(TargetPointer);
	}
}

void ATargettingSystem::RemoveTarget(UTargetComponent * newTarget)
{
	if (newTarget)
	{
		TWeakObjectPtr<UTargetComponent> TargetPointer{ newTarget };
		TargetComponents.RemoveSingleSwap(TargetPointer);
	}
}

