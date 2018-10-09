// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetSelectionComponent.generated.h"

class ATargetReticle;
class UTargetComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOVERGAME_API UTargetSelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetSelectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	
		UFUNCTION(BlueprintCallable,Category = Targetting)
	virtual void UpdateTargetting(FTransform Aim,float DeltaTime, bool bSelectTargets);


	UPROPERTY(BlueprintReadWrite, Category = Targetting)
	TArray<UTargetComponent*> SelectedTargets;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Targetting)
	float TargetCooldown;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targetting)
	int MaxTargets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targetting)
	float TargettingAngleDegrees;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targetting)
		float TargettingMaxDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targetting)
		TSubclassOf<ATargetReticle> TargetReticleClass;

	float TimeToTarget;

	
};
