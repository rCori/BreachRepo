// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageDoor.h"


// Sets default values
AGarageDoor::AGarageDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GarageDoorMesh"));
	DoorFrameMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGarageDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGarageDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGarageDoor::InGameEvent_Implementation(){
}

