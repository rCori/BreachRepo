// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTestInterface.h"
#include "CPP_Door.generated.h"

UCLASS()
class BREACH_API ACPP_Door : public AActor, public IMyTestInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void MyFunctionToImplement();
	virtual void MyFunctionToImplement_Implementation(); // This is the declaration of the implementation
	
};
