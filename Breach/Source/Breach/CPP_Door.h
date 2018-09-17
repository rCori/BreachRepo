// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_GenericInGameEvent.h"
#include "CPP_Door.generated.h"

UCLASS()
class BREACH_API ACPP_Door : public AActor, public ICPP_GenericInGameEvent
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

	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void InGameEvent();
	virtual void InGameEvent_Implementation(); // This is the declaration of the implementation
	
	UFUNCTION(BlueprintCallable)
	void ToggleDoor();

	UFUNCTION(BlueprintImplementableEvent, Category="DoorUsageMechanics")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category="DoorUsageMechanics")
	void CloseDoor();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "DoorProperties")
	bool IsLocked;

	UPROPERTY(BlueprintReadWrite)
	bool IsOpen;

	UPROPERTY(BlueprintReadWrite)
	bool FirstCollision;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "DoorProperties")
	bool UnlocksOnEvent;

	UPROPERTY(BlueprintReadWrite)
	bool PlayerInRange;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "DoorProperties", Meta = (MakeEditWidget = true))
	FVector WaypointOffset;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "DoorProperties")
	FString EventTag;

	/*
	IsLocked:boolean=false public
	IsOpen:boolean = false
	FirstCollision:boolean =true
	UnlocksOnEvent:boolean=false public
	PlayerInRange:boolean=false
	WaypointOffest:Vector3=(0,0,0)
	EventTag:String=""

	*/

};
