// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Door.h"


// Sets default values
ACPP_Door::ACPP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorFrameMesh);

	//Set defaults for UPROPERTYs
	IsLocked = false;
	IsOpen = false;
	FirstCollision = true;
	UnlocksOnEvent = false;
	PlayerInRange = false;
	WaypointOffset = FVector(0.0,0.0,0.0);
	EventTag="";
}

// Called when the game starts or when spawned
void ACPP_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Door::ToggleDoor(){
	//Check if IsOpen
	if(IsOpen){
		//Call Close Door
		CloseDoor();
	} else {
		//Call Open Door
		OpenDoor();
	}
	IsOpen = !IsOpen;
}

void ACPP_Door::InGameEvent_Implementation(){
}


