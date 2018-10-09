// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/DamageTypes.h"
#include "DamageComponent.generated.h"





UENUM(BlueprintType)
enum class EDamageOwnerType : uint8 {
	//Owner is a NPC character (enemy, friendly, etc)
	NPC,
	//Owner is a player
	PlayerCharacter,
	//Owner is an environment prop
	Environment,
	//Owner doesnt fit in the other categories
	Other
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageDelegate, FHoverDamageEvent, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathDelegate, FHoverDeathEvent, Event);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOVERGAME_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	//normal damage event for routing
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	//official damage event
	UFUNCTION(BlueprintCallable, Category = Damage)
		float ApplyDamage(FHitResult Hit, TSubclassOf<UDamageType> DamageType, float BaseDamage, AController * InstigatorController, AActor * DamageCauser);
	//restores health
	UFUNCTION(BlueprintCallable, Category = Damage)
		float ApplyHeal(float BaseHeal, AActor * Healer, AController * HealInstigator);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Damage)
		float GetHealth()const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Damage)
		bool IsDead()const;

	//returns health ratio from 0 at 0 health to 1 at full health
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Damage)
		float GetHealthRatio() const;

	//sets the health. Gets clamped beetween 0 and MaxHealth
	UFUNCTION(BlueprintCallable, Category = Damage)
		void SetHealth(float newHealth);

	//resets everything and resurrects
	UFUNCTION(BlueprintCallable, Category = Damage)
		void Restore();

	//Maximum possible health, also starting health
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = Damage)
		float MaxHealth;
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = Damage)
		bool bIsInvulnerable;

	//triggers the delegate events. Set to false to disable the delegates
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = Damage)
		bool bBroadcastGlobalEvents;

		//Delegate that triggers on death. Will only be called once
	UPROPERTY(BlueprintAssignable, Category = Damage)
		FDeathDelegate OnDeath;

	//delegate that triggers on damage. Doesnt trigger if its already dead
	UPROPERTY(BlueprintAssignable, Category = Damage)
		FDamageDelegate OnLocalDamage;

	UPROPERTY(BlueprintReadWrite, Category = Damage)
		EDamageOwnerType DamageOwnerType;

protected:
	

	UPROPERTY(Replicated)
		bool bIsDead;	

	UPROPERTY(Replicated)
		float CurrentHealth;
};
