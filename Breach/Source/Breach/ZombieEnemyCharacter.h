// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieEnemyCharacter.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UAnimMontage;
class ACPP_FirstPersonCharacter;

UCLASS()
class BREACH_API AZombieEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieEnemyCharacter();

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category=Mesh)
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category=Attack)
	UBoxComponent* AttackRange;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DoAttack(ACPP_FirstPersonCharacter* firstPersonCharacter);
	
	
};
