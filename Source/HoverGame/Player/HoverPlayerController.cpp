// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverPlayerController.h"
#include "Kismet/GameplayStatics.h"




void AHoverPlayerController::Pause()
{
	if (!GetWorld()->IsPaused())
	{
		bool paused = SetPause(true); 

		if (paused)
		{
			OnPaused();
		}
		
	}	
}

void AHoverPlayerController::Unpause()
{

	if (GetWorld()->IsPaused())
	{
		SetPause(false);
		
		OnUnpaused();		
	}
	
}
