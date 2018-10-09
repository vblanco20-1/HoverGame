// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageComponent.h"

#include "HoverGame.h"
#include "UnrealNetwork.h"
#include "Game/HoverGameInstance.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	bIsDead = false;
	MaxHealth = 100;
	bIsInvulnerable = false;
	bReplicates = true;
	DamageOwnerType = EDamageOwnerType::NPC;
	bBroadcastGlobalEvents = true;
	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	bIsDead = false;
	
	// ...
	
}
float UDamageComponent::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return ApplyDamage(FHitResult(), DamageEvent.DamageTypeClass, Damage, EventInstigator, DamageCauser);

	
}
void UDamageComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageComponent, CurrentHealth);
	DOREPLIFETIME(UDamageComponent, MaxHealth);
	DOREPLIFETIME(UDamageComponent, bIsInvulnerable);
	DOREPLIFETIME(UDamageComponent, bIsDead);
}


// Called every frame
//void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}


float UDamageComponent::ApplyDamage(FHitResult Hit, TSubclassOf<UDamageType> DamageType, float BaseDamage, AController * InstigatorController, AActor * DamageCauser)
{
	if (bIsDead)
	{
		return 0.f;
	}
	FHoverDamageEvent DmgEvent;
	DmgEvent.BaseDamage = BaseDamage;
	DmgEvent.DamageCauser = DamageCauser;
	DmgEvent.DamageType = DamageType;
	DmgEvent.Hit = Hit;
	DmgEvent.InstigatorController = InstigatorController;

	OnLocalDamage.Broadcast(DmgEvent);//Hit, BaseDamage, InstigatorController, DamageCauser);

	UHoverGameInstance * GameInstance = GetWorld()->GetGameInstance<UHoverGameInstance>();
	if (GameInstance && bBroadcastGlobalEvents)
	{
		GameInstance->NotifyDamageEvent(this, DmgEvent);
	}
	
	if (bIsInvulnerable)
	{
		TRACE("Invulnerable");
		BaseDamage = 0;
	}
	if (GetNetMode() >= NM_Client)
	{
		TRACE("Clients cant cause damage directly");
	}
	else
	{
		//if (GetOwner()->IsA(ADGN_BasePlayerCharacter::StaticClass()))
		//{
		//	float Multiplier = GetWorld()->GetAuthGameMode()->GetNumPlayers();
		//	BaseDamage *= FMath::Clamp(Multiplier, 1.0f, 2.5f);
		//}
		//if (GetOwner()->IsA(ADGN_EnemyBase::StaticClass()))
		//{
		//	Cast<ADGN_EnemyBase>(GetOwner())->AggroDistance = 9999999;
		//}
		//
		//if (Hit.Component.IsValid())
		//{
		//	UDGN_MeleeCombatComponent* c = Hit.Actor->FindComponentByClass<UDGN_MeleeCombatComponent>();
		//	if (c)
		//	{
		//		if (c->BlockHit(Hit, true))
		//		{
		//			return 0.f;
		//		}
		//	}
		//}

		TRACE("Damaged For %s Damage", *FString::SanitizeFloat(BaseDamage) );

		SetHealth(CurrentHealth - BaseDamage);
		//CurrentHealth -= BaseDamage;

		if (CurrentHealth <= 0.0f)
		{
			//if (GetOwner()->IsA(ADGN_EnemyBase::StaticClass()))
			//{
			//	UDGN_GameplayFunctions::RemoveEntityBoid(GetOwner()->FindComponentByClass<UECS_ComponentSystemLink>());
			//}
			//
			//
			//Multicast_DeathEvent(InstigatorController, DamageCauser);

			FHoverDeathEvent DeathEvent;
			DeathEvent.DamageCauser = DamageCauser;
			DeathEvent.InstigatorKiller = InstigatorController;

			
			OnDeath.Broadcast(DeathEvent);
			if (GameInstance && bBroadcastGlobalEvents)
			{
				GameInstance->NotifyDeathEvent(this, DeathEvent);
			}
			bBroadcastGlobalEvents = false;
			bIsDead = true;
		}

		//if (GetOwner())
		//{
		//	FPointDamageEvent DmgEvent;
		//	DmgEvent.DamageTypeClass = DamageType;
		//	DmgEvent.Damage = BaseDamage;
		//	DmgEvent.HitInfo = Hit;
		//
		//	//GetOwner()->TakeDamage(BaseDamage, DmgEvent, InstigatorController, DamageCauser);
		//
		//	FVector HitLoc = FVector::ZeroVector;
		//	//if (HitLoc.Size() > 1.0)
		//	//{
		//	HitLoc = GetOwner()->GetActorLocation() + FVector(0, 0, 30);
		//
		//	//}
		//
		//
		//
		//	FDamageTextEvent TextEvent;
		//	TextEvent.InitialTransform.SetLocation(HitLoc);
		//	TextEvent.InitialVelocity = FMath::VRandCone(FVector(0, 0, 1), FMath::DegreesToRadians(40)) * 50;
		//	TextEvent.DamageType = DamageType;
		//	TextEvent.DamageAmount = BaseDamage;
		//
		//	Multicast_CreateDamageText(TextEvent);
		//
		//
		//	//
		//}
	}




	return BaseDamage;
}

float UDamageComponent::ApplyHeal(float BaseHeal, AActor * Healer, AController * HealInstigator)
{
	float NewHealth = FMath::Clamp(CurrentHealth + BaseHeal, 0.f, MaxHealth);
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, GetNameSafe(this) + " Healed from : " + FString::SanitizeFloat(CurrentHealth) + " to: " + FString::SanitizeFloat(NewHealth));

	SetHealth(NewHealth);
	return BaseHeal;
}

float UDamageComponent::GetHealth()const
{
	return CurrentHealth;
}

bool UDamageComponent::IsDead() const
{
	return bIsDead;
}

float UDamageComponent::GetHealthRatio() const
{
	return CurrentHealth / MaxHealth;
}

void UDamageComponent::SetHealth(float newHealth)
{

	CurrentHealth = FMath::Clamp(newHealth, 0.f, MaxHealth);
	//if (HealthbarMaterialInstance)
	//{
	//	HealthbarMaterialInstance->SetScalarParameterValue("HealthRatio", GetHealthRatio());
	//}
}

void UDamageComponent::Restore()
{
	bIsDead = false;
	SetHealth(MaxHealth);
}

