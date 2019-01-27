// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieEnemyCharacter.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UAnimMontage;
class ACPP_FirstPersonCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogAttackRange, Log, All);

UCLASS()
class BREACH_API AZombieEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieEnemyCharacter();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category=Attack)
	UBoxComponent* AttackRange;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category=Gameplay)
	UBoxComponent* HitBox;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* AttackAnimation;

	UPROPERTY(BlueprintReadOnly, Category=Attack)
	ACPP_FirstPersonCharacter* firstPersonCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool isAttackRange;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float walkSpeed;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Health")
	float health;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Health")
	bool hasDied;

	float attackCooldown;
	float attackRate;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SetIsInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void SetNotInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void DoAttack();
	
	UFUNCTION(BlueprintCallable)
	bool IsReadyToAttack();
	
};
