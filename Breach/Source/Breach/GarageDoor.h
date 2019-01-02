// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_GenericInGameEvent.h"
#include "GarageDoor.generated.h"

UCLASS()
class BREACH_API AGarageDoor : public AActor, public ICPP_GenericInGameEvent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGarageDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void InGameEvent();
	virtual void InGameEvent_Implementation(); // This is the declaration of the implementation

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorFrameMesh;
	
};
