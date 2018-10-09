// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverProjectile.h"


// Sets default values
AHoverProjectile::AHoverProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseDamage = 10;
}

// Called when the game starts or when spawned
void AHoverProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoverProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

