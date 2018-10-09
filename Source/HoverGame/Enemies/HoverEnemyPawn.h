// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverEnemyInterface.h"
#include "HoverEnemyPawn.generated.h"


/* Subclass for Pawn based enemies. Redirects damage to the component
*/
UCLASS()
class HOVERGAME_API AHoverEnemyPawn : public APawn, public IHoverEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHoverEnemyPawn();

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
