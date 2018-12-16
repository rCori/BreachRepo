// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractArea.h"
#include "Components/BoxComponent.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

// Sets default values
AInteractArea::AInteractArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AInteractArea::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractArea::SetIsInRange);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractArea::SetNotInRange);
	interactionState = InteractionState::begin;

}

// Called every frame
void AInteractArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractArea::SetIsInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(PlayerClass != nullptr){
		if(PlayerClass->IsChildOf(OtherActor->StaticClass())){
			IsInRangeInteract.Broadcast(true);
		} 
	}
}

void AInteractArea::SetNotInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(PlayerClass != nullptr){
		if(PlayerClass->IsChildOf(OtherActor->StaticClass())){
			IsInRangeInteract.Broadcast(false);
		}
	}
}

void AInteractArea::DoInteraction(){
	switch(interactionState){
		case InteractionState::begin:
			if(InteractionDialog == nullptr){
				InteractionDialog = CreateWidget<UUserWidget>(GetGameInstance(), InteractionDialogWidget);
			}
			//Some error could occur between these two conditionals, making this extra check necessary
			if(InteractionDialog != nullptr){
				InteractionDialog->AddToViewport();
			}
			interactionState = InteractionState::end;
			break;
		case InteractionState::middle:
			//Advance the dialog
			break;
		case InteractionState::end:
			if(InteractionDialog != nullptr){
				InteractionDialog->RemoveFromViewport();
			}
			interactionState = InteractionState::begin;
			break;
		default:
			break;
	}
}