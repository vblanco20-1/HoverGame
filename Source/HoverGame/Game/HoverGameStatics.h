// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HoverGameStatics.generated.h"

/**
 * 
 */

class ATargettingSystem;

UCLASS()
class HOVERGAME_API UHoverGameStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	//iterates all actors in the map and finds the closest one
		UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
		static AActor * GetClosestActorOfClass(UObject* WorldContextObject, FVector Origin, TSubclassOf<AActor> Classes);

		//returns all the actors in a radius (uses actor center)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
		static TArray<AActor*> GetActorsInSphere(UObject* WorldContextObject, FVector Origin, float Radius, TSubclassOf<AActor> Classes);

	//returns all the actors inside a cone (uses actor center)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
		static TArray<AActor*> GetActorsInCone(UObject* WorldContextObject, FVector Origin, FVector Direction, float AngleRad, float MaxDistance, TSubclassOf<AActor> Classes);

	//finds the actor that is more "centered" to the direction
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
		static AActor* GetActorWithLessAngle(UObject* WorldContextObject, FVector Origin, FVector Direction, TSubclassOf<AActor> Classes);

	//find the closest element in an actor array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay)
		static AActor* GetClosestActorFromArray(TArray<AActor*> Array, FVector Origin);
	

	//Grab targetting system. It will spawn one if there isnt one in the map
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
		static ATargettingSystem* FindTargettingSystem(UObject* WorldContextObject);

	//Grab activation system. It will spawn one if there isnt one in the map
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Gameplay, Meta = (WorldContext = "WorldContextObject"))
	static AActivationSystem* FindActivationSystem(UObject* WorldContextObject);
};
