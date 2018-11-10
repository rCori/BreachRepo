// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHealthComponent.h"


// Sets default values for this component's properties
UPlayerHealthComponent::UPlayerHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	health = MaxHealth;
	timeSinceDamage = 0.0f;

	// ...
	
}


// Called every frame
void UPlayerHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	timeSinceDamage += DeltaTime;
	if(health < MaxHealth && timeSinceDamage > TimeUntilRegen){
		health += RegenRate * DeltaTime;
		if(health > MaxHealth){
			health = MaxHealth;
		}
		OnHealthChanged.Broadcast(health);
	}
}

void UPlayerHealthComponent::TakeDamage(float damageAmount)
{
	health -= damageAmount;
	OnHealthChanged.Broadcast(health);
	if(health <= 0.0f){
		OnPlayerDied.Broadcast();
	}
	timeSinceDamage = 0.0f;
}

float UPlayerHealthComponent::GetHealth()
{
	return health;
}