// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverEnemyCharacter.h"
#include "Components/DamageComponent.h"

// Sets default values
AHoverEnemyCharacter::AHoverEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoverEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoverEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoverEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AHoverEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//route the take damage through the damage component
	UActorComponent *DmgComponent = GetComponentByClass(UDamageComponent::StaticClass());
	if (IsValid(DmgComponent))
	{
		return Cast<UDamageComponent>(DmgComponent)->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}
	else //default to normal
	{
		return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}
}

