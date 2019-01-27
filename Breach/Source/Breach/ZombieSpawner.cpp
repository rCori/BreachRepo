// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieSpawner.h"
#include "ZombieEnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AZombieSpawner::AZombieSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 static ConstructorHelpers::FClassFinder<AZombieEnemyCharacter> ZombieCharacterClassTemp(TEXT("/Game/BlueprintSource/ZombieEnemy/BP_ZombieEnemyCharacter"));
     if (ZombieCharacterClassTemp.Class != NULL)
     {
         ZombieCharacterClass = ZombieCharacterClassTemp.Class;
     }
}

// Called when the game starts or when spawned
void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSpawner::SpawnAllZombies()
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;
	ActorSpawnParameters.Instigator = Instigator;
	FVector actorLocation = GetActorLocation();
	for(int i = 0; i < SpawnLocations.Num(); i++){
		if(GetWorld()){
			FRotator rotator = FRotator(0.0,0.0,0.0);
			AZombieEnemyCharacter* SpawnedActor1 = GetWorld()->SpawnActor<AZombieEnemyCharacter>(ZombieCharacterClass, actorLocation + SpawnLocations[i],rotator,ActorSpawnParameters);
		}
	}
}

void AZombieSpawner::InGameEvent_Implementation()
{
	//SpawnAllZombies();
}

