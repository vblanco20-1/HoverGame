// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverGameStatics.h"
#include "HoverGame.h"

#include "Game/TargettingSystem.h"

#include "Engine.h"




AActor * UHoverGameStatics::GetClosestActorOfClass(UObject* WorldContextObject, FVector Origin, TSubclassOf<AActor> Classes)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	AActor * ClosestActor = nullptr;
	for (TActorIterator<AActor> ActorItr(World, Classes); ActorItr; ++ActorItr)
	{
		if (ClosestActor == nullptr)
		{
			ClosestActor = *ActorItr;
		}
		else
		{
			const float oldDist = FVector::Dist(ClosestActor->GetActorLocation(), Origin);
			const float newDist = FVector::Dist(ActorItr->GetActorLocation(), Origin);
			if (newDist < oldDist)
			{
				ClosestActor = *ActorItr;
			}
		}
	}

	return ClosestActor;
}

TArray<AActor*> UHoverGameStatics::GetActorsInSphere(UObject* WorldContextObject, FVector Origin, float Radius, TSubclassOf<AActor> Classes)
{
	TArray<AActor*> Array;

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	for (TActorIterator<AActor> ActorItr(World, Classes); ActorItr; ++ActorItr)
	{
		AActor * TestActor = *ActorItr;

		const float Dist = FVector::Dist(TestActor->GetActorLocation(), Origin);

		if (Dist < Radius)
		{
			Array.Add(TestActor);
		}

	}



	return Array;
}

TArray<AActor*> UHoverGameStatics::GetActorsInCone(UObject* WorldContextObject, FVector Origin, FVector Direction, float AngleRad, float MaxDistance, TSubclassOf<AActor> Classes)
{
	TArray<AActor*> Array;

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	Direction.Normalize();
	for (TActorIterator<AActor> ActorItr(World, Classes); ActorItr; ++ActorItr)
	{
		AActor * TestActor = *ActorItr;

		const float Dist = FVector::Dist(TestActor->GetActorLocation(), Origin);

		if (Dist < MaxDistance)
		{


			FVector OriginToActor = TestActor->GetActorLocation() - Origin;
			OriginToActor.Normalize();

			float angle = FMath::Acos(FVector::DotProduct(Direction, OriginToActor));

			if (FMath::Abs(angle) < AngleRad)
			{
				Array.Add(TestActor);
			}

		}

	}

	return Array;
}


AActor* UHoverGameStatics::GetActorWithLessAngle(UObject* WorldContextObject, FVector Origin, FVector Direction, TSubclassOf<AActor> Classes)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	AActor * ClosestActor = nullptr;
	float LastAngle = 0;
	for (TActorIterator<AActor> ActorItr(World, Classes); ActorItr; ++ActorItr)
	{
		if (ClosestActor == nullptr)
		{
			ClosestActor = *ActorItr;
			FVector OriginToActor = ClosestActor->GetActorLocation() - Origin;
			OriginToActor.Normalize();

			LastAngle = FMath::Acos(FVector::DotProduct(Direction, OriginToActor));

		}
		else
		{
			FVector OriginToActor = ActorItr->GetActorLocation() - Origin;
			OriginToActor.Normalize();

			float NewAngle = FMath::Acos(FVector::DotProduct(Direction, OriginToActor));

			if (NewAngle < LastAngle)
			{
				ClosestActor = *ActorItr;
				LastAngle = NewAngle;
			}
		}
	}

	return ClosestActor;
}

AActor* UHoverGameStatics::GetClosestActorFromArray(TArray<AActor*> Array, FVector Origin)
{

	AActor * ClosestActor = nullptr;
	if (Array.IsValidIndex(0))
	{
		for (auto a : Array)
		{
			if (ClosestActor == nullptr)
			{
				ClosestActor = a;
			}
			else
			{
				const float oldDist = FVector::Dist(ClosestActor->GetActorLocation(), Origin);
				const float newDist = FVector::Dist(a->GetActorLocation(), Origin);
				if (newDist < oldDist)
				{
					ClosestActor = a;
				}
			}
		}
	}

	return ClosestActor;
}

ATargettingSystem * UHoverGameStatics::FindTargettingSystem(UObject * WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	
	ATargettingSystem * TargetSys = nullptr;
	for (TActorIterator<ATargettingSystem> ActorItr(World); ActorItr; ++ActorItr)
	{
		TargetSys= *ActorItr;
	}

	if (TargetSys == nullptr)
	{
		TargetSys = World->SpawnActor<ATargettingSystem>();
		if (TargetSys == nullptr)
		{
			TRACESTATIC("Trying to create target system failed");
		}
	}
	return TargetSys;
}
