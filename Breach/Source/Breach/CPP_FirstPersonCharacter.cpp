// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_FirstPersonCharacter.h"
#include "CPP_FirstPersonGameMode.h"
#include "PlayerHealthComponent.h"


// Sets default values
ACPP_FirstPersonCharacter::ACPP_FirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	healthComp = CreateDefaultSubobject<UPlayerHealthComponent>(TEXT("healthComp"));
}

// Called when the game starts or when spawned
void ACPP_FirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	canMove = true;
	hasSCAR = false;
	
}

// Called every frame
void ACPP_FirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_FirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_FirstPersonCharacter::SetCanMove(bool _canMove){
	canMove = _canMove;
}

bool ACPP_FirstPersonCharacter::GetCanMove(){
	return canMove;
}

void ACPP_FirstPersonCharacter::ObtainSCAR(){
	hasSCAR = true;
	if(GetWorld()) {
		ACPP_FirstPersonGameMode* gamemode = Cast<ACPP_FirstPersonGameMode>(GetWorld()->GetAuthGameMode());
		gamemode->ChangeOnScreenMessage.Broadcast("Press Q to switch to SCAR",2);
	}

}