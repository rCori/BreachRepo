// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSCAR.h"
#include "CPP_FirstPersonGameMode.h"
#include "Components/BoxComponent.h"
#include "CPP_FirstPersonCharacter.h"
#include "CPP_GenericInGameEvent.h"


// Sets default values
APickupSCAR::APickupSCAR()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SCARMesh"));
	GunMesh->bCastDynamicShadow = true;
	GunMesh->CastShadow = true;
	GunMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupSCAR::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupSCAR::SetIsInRange);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APickupSCAR::SetNotInRange);
	
}

// Called every frame
void APickupSCAR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupSCAR::SetIsInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACPP_FirstPersonCharacter* playerCharacter = Cast<ACPP_FirstPersonCharacter>(OtherActor);
	if(playerCharacter != nullptr){
		BindToCharacterIsUsing(playerCharacter,true);
		if(GetWorld()) {
			ACPP_FirstPersonGameMode* gamemode = Cast<ACPP_FirstPersonGameMode>(GetWorld()->GetAuthGameMode());
			gamemode->ChangeOnScreenMessage.Broadcast("Press E to Pickup SCAR",1000);
		}
	} 
}

void APickupSCAR::SetNotInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPP_FirstPersonCharacter* playerCharacter = Cast<ACPP_FirstPersonCharacter>(OtherActor);
	if(playerCharacter != nullptr){
		BindToCharacterIsUsing(playerCharacter,false);
		if(GetWorld()) {
			ACPP_FirstPersonGameMode* gamemode = Cast<ACPP_FirstPersonGameMode>(GetWorld()->GetAuthGameMode());
			gamemode->ChangeOnScreenMessage.Broadcast("",2);
		}
	}
}


void APickupSCAR::AwardSCAR(ACPP_FirstPersonCharacter* firstPersonCharacter){
	firstPersonCharacter->ObtainSCAR();
	if(genericInGameEvent != nullptr){
		//This is some weird C++ workaround mentioned on this wiki page
		//https://wiki.unrealengine.com/Interfaces_And_Blueprints
		if (genericInGameEvent->GetClass()->ImplementsInterface(UCPP_GenericInGameEvent::StaticClass()))
		{
		  ICPP_GenericInGameEvent::Execute_InGameEvent(genericInGameEvent);
		}

		//Because this does not work apparently
		/*ICPP_GenericInGameEvent* eventObjTemp = Cast<ICPP_GenericInGameEvent>(genericInGameEvent);
		if(eventObjTemp != nullptr){
			eventObjTemp->InGameEvent();
		}*/
	}
	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &APickupSCAR::SetIsInRange);
	BoxComponent->OnComponentEndOverlap.RemoveDynamic(this, &APickupSCAR::SetNotInRange);
	Destroy();
}