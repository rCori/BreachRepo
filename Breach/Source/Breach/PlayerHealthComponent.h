// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,float,currentHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BREACH_API UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDied OnPlayerDied;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageAmount);

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Health")
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Health")
	float TimeUntilRegen;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Health")
	float RegenRate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY()
	float timeSinceDamage;

	UPROPERTY()
	float health;
	
};
