// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_FirstPersonGameMode.h"
#include "CPP_WaypointWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"




void ACPP_FirstPersonGameMode::CreateWaypoint(AActor *actor, FString tag, FVector waypointOffset){
	//Inventory widget setup
    WidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), WidgetTemplate);
	//APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	WidgetInstance->AddToViewport();
	//We can't do this because that's a blueprint.
	//Now we can because we made a c++ class
	UCPP_WaypointWidget* waypointWidget = Cast<UCPP_WaypointWidget>(WidgetInstance);
	waypointWidget->AttachActor = actor;
}