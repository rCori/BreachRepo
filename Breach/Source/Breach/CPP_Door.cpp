// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Door.h"


// Sets default values
ACPP_Door::ACPP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ACPP_Door::MyFunctionToImplement_Implementation(){
}

