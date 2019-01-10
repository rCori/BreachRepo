// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieEnemyCharacter.h"
#include "PlayerHealthComponent.h"
#include "CPP_FirstPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AZombieEnemyCharacter::AZombieEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->bCastDynamicShadow = true;
	CharacterMesh->CastShadow = true;
	CharacterMesh->SetupAttachment(RootComponent);

	AttackRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	AttackRange->SetupAttachment(RootComponent);
	AttackRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AZombieEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombieEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Attempt an attack if the player is within bounds
void AZombieEnemyCharacter::DoAttack(ACPP_FirstPersonCharacter* firstPersonCharacter)
{
	TSubclassOf<UPlayerHealthComponent> playerHealthClass;
	UPlayerHealthComponent* healthComponent = Cast<UPlayerHealthComponent>(firstPersonCharacter->GetComponentByClass(playerHealthClass));
	healthComponent->TakeDamage(30.0f);

}
