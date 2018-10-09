// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes.generated.h"

//Core "Damage" event
USTRUCT(BlueprintType)
struct FHoverDamageEvent
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		FHitResult Hit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		float BaseDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		TWeakObjectPtr<AController>  InstigatorController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		TWeakObjectPtr<AActor> DamageCauser;
};

//general death event
USTRUCT(BlueprintType)
struct FHoverDeathEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		TWeakObjectPtr<AController> InstigatorKiller;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Damage)
		TWeakObjectPtr<AActor> DamageCauser;
};

