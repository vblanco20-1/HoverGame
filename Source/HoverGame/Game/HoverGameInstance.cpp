// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverGameInstance.h"




void UHoverGameInstance::NotifyDamageEvent(UDamageComponent * EventInstigator, const FHoverDamageEvent &Event)
{
	OnDamageEvent.Broadcast(EventInstigator, Event);
}

void UHoverGameInstance::NotifyDeathEvent(UDamageComponent * EventInstigator, const FHoverDeathEvent & Event)
{
	OnDeathEvent.Broadcast(EventInstigator, Event);
}

void UHoverGameInstance::BroadcastPlayerMessage(UObject * EventInstigator, APlayerController* Target, FText Message)
{
	OnPlayerMessageEvent.Broadcast(EventInstigator, Target, Message);
}
