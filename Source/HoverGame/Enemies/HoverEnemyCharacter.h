// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HoverEnemyInterface.h"
#include "HoverEnemyCharacter.generated.h"


/* Subclass for Character based enemies. Redirects damage to the component
*/

UCLASS()
class HOVERGAME_API AHoverEnemyCharacter : public ACharacter, public IHoverEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHoverEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
};
