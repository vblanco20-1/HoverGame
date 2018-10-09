// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoverEnemyInterface.generated.h"


UINTERFACE(BlueprintType)
class HOVERGAME_API UHoverEnemyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class HOVERGAME_API IHoverEnemyInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	//nothing for now, tag only
	
};