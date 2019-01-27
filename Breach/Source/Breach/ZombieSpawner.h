// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_GenericInGameEvent.h"
#include "ZombieEnemyCharacter.h"
#include "ZombieSpawner.generated.h"

UCLASS()
class BREACH_API AZombieSpawner : public AActor,  public ICPP_GenericInGameEvent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieSpawner();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Meta = (MakeEditWidget = true))
	TArray<FVector> SpawnLocations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AZombieEnemyCharacter> ZombieCharacterClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnAllZombies();
	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void InGameEvent();
	virtual void InGameEvent_Implementation(); // This is the declaration of the implementation
	
};
