// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_NewLevelLoad.h"
#include "Components/BoxComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ACPP_NewLevelLoad::ACPP_NewLevelLoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot")); 
	SceneComponent->SetMobility(EComponentMobility::Movable);
	RootComponent = SceneComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ACPP_NewLevelLoad::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_NewLevelLoad::LoadLevel);
}

// Called every frame
void ACPP_NewLevelLoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Load the level
//This will be assigned as a OnComponentBeginOverlap
void ACPP_NewLevelLoad::LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Is the other actor a subclass of type FirstPersonCharacterClass
	if(FirstPersonCharacterClass->IsChildOf(OtherActor->StaticClass())){
		UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), LoadLevelWidget);
		WidgetInstance->AddToViewport();
		UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), TRAVEL_Absolute);
	}
}