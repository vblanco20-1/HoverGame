// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HoverPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOVERGAME_API AHoverPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


	//Pauses the game safely, calling events
	UFUNCTION(BlueprintCallable, Category = Game)
	void PauseGame();

	//unpauses the game safely, calling events
	UFUNCTION(BlueprintCallable, Category = Game)
		void Unpause();

	UFUNCTION(BlueprintImplementableEvent, Category = Game)
		void OnPaused();

	UFUNCTION(BlueprintImplementableEvent, Category = Game)
		void OnUnpaused();
};
