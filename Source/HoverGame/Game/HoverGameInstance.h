// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Types/DamageTypes.h"
#include "HoverGameInstance.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageEventDelegate, UDamageComponent*,EventInstigator, FHoverDamageEvent, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeathEventDelegate, UDamageComponent*,EventInstigator, FHoverDeathEvent, Event);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPlayerMessageEventDelegate, UObject*, EventInstigator, APlayerController*, Target , FText, Message);

/*
*
*	Global class. Holds some global events that missions can use
*/
UCLASS()
class HOVERGAME_API UHoverGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	void NotifyDamageEvent(UDamageComponent * EventInstigator,const FHoverDamageEvent &Event);

	void NotifyDeathEvent(UDamageComponent * EventInstigator, const FHoverDeathEvent &Event);
	
	UFUNCTION(BlueprintCallable,Category = Game)
	void BroadcastPlayerMessage(UObject * EventInstigator, APlayerController* Target, FText Message);


	//Triggers when someone dies, global
	UPROPERTY(BlueprintAssignable, Category = Damage)
		FDeathEventDelegate OnDeathEvent;

	//Triggers when someone gets damaged, global
	UPROPERTY(BlueprintAssignable, Category = Damage)
		FDamageEventDelegate OnDamageEvent;


	UPROPERTY(BlueprintAssignable, Category = Damage)
		FPlayerMessageEventDelegate OnPlayerMessageEvent;
};
