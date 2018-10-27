// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_FirstPersonGameMode.h"
#include "CPP_WaypointWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"



ACPP_FirstPersonGameMode::ACPP_FirstPersonGameMode(const FObjectInitializer & ObjectInitializer){
	UE_LOG(LogTemp, Log, TEXT("ACCP_FirstPersonGameMode: Consturctor"));
	//WaypointWidgets = TMap<FString, UUserWidget*>();
	//Inventory widget setup
    //PauseMenu = CreateWidget<UUserWidget>(GetGameInstance(), PauseTemplate);
}

void ACPP_FirstPersonGameMode::CreateWaypoint(AActor *actor, FString tag, FVector waypointOffset){
	/*
	if(WaypointWidgets == nullptr){
		UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: WaypointWidgets is being initialized in CreateWaypoint"));
		WaypointWidgets = TMap<FString, UUserWidget*>();
	}
	*/
	//Inventory widget setup
	
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: Trying CreateWaypoint"));
	if(GetWorld()== nullptr){
		UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: GetWorld returns nullptr"));
	}
    WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: CreateWaypoint Widget created"));
	if(WidgetInstance == nullptr){
		UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: WidgetInstance is nullptr"));
	}
	
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: CreateWaypoint Widget Added to Viewport"));
	UCPP_WaypointWidget* waypointWidget = Cast<UCPP_WaypointWidget>(WidgetInstance);
	if(waypointWidget == nullptr){
		UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: waypointWidget casts nullptr"));
	}
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: CreateWaypoint cast succeeded"));
	waypointWidget->AttachActor = actor;
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: AttachActor"));
	waypointWidget->LocationOffset = waypointOffset;
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: LocationOffset"));
	WaypointWidgets.Add(tag,waypointWidget);
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: Add to WaypointWidgets"));

	//APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	WidgetInstance->AddToViewport();
	UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: After Adding to Viewport"));
	
}

void ACPP_FirstPersonGameMode::RemoveWaypoint(FString tag){
	/*
	if(WaypointWidgets == nullptr){
		UE_LOG(LogTemp, Log, TEXT("ACPP_FirstPersonGameMode: WaypointWidgets is being initialized in RemoveWaypoint"));
		WaypointWidgets = new TMap<FString, UUserWidget*>();
	}
	*/
	
	//Check if the tag we are requesting to remove actually exists
	if(WaypointWidgets.Contains(tag)){
		//Get a reference so we can remove it
		UCPP_WaypointWidget* waypointWidgetToRemove = Cast<UCPP_WaypointWidget>(WaypointWidgets[tag]);
		if(waypointWidgetToRemove != nullptr){
			//Remove the widget form the parent(which in this case is always the viewport
			waypointWidgetToRemove->RemoveFromParent();
			//Remove the waypoint with this tag from the list
			WaypointWidgets.Remove(tag);
		}
	}
	
}

void ACPP_FirstPersonGameMode::PauseGame(){
	if(PauseMenu == nullptr){
		PauseMenu = CreateWidget<UUserWidget>(GetGameInstance(), PauseTemplate);
	}
	if(PauseMenu != nullptr){
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if(playerController != nullptr){
			playerController->SetPause(true);
			PauseMenu->AddToViewport();
			//Hey you need to GetCachedWidget if you want to focus input on only one widget.
			//Ths internet will not tell you except for this one guy
			//https://answers.unrealengine.com/questions/138594/focus-issue-when-adding-umg-widget-in-code.html
			//Eat my butt forever WCode
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(PauseMenu->GetCachedWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			playerController->SetInputMode(InputModeData);
			playerController->bShowMouseCursor = true; 
		}
	}
}

void ACPP_FirstPersonGameMode::UnpauseGame(){
	if(PauseMenu == nullptr){
		PauseMenu = CreateWidget<UUserWidget>(GetGameInstance(), PauseTemplate);
	}
	if(PauseMenu != nullptr){
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if(playerController != nullptr){
			playerController->SetPause(false);
			PauseMenu->RemoveFromParent();
			FInputModeGameOnly InputModeData;
			playerController->SetInputMode(InputModeData);
			playerController->bShowMouseCursor = false; 
		}
	}
}