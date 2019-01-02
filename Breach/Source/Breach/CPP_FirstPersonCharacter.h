// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_FirstPersonCharacter.generated.h"

UCLASS()
class BREACH_API ACPP_FirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_FirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool canMove;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool hasSCAR;

	UFUNCTION()
	void SetCanMove(bool _canMove);

	UFUNCTION(BlueprintCallable)
	bool GetCanMove();

	UFUNCTION()
	void ObtainSCAR();
};
