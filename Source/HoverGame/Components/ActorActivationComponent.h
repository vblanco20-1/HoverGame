// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorActivationComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAreaEnterDelegate, APawn*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAreaExitDelegate, APawn*, Player);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOVERGAME_API UActorActivationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorActivationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Component)
	bool bActivateByDistance{ true };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	float ActivationDistance = 100;
	UPROPERTY(BlueprintAssignable, Category = Component)
	FAreaEnterDelegate PlayerEntered;
	UPROPERTY(BlueprintAssignable, Category = Component)
	FAreaExitDelegate PlayerExited;
};
