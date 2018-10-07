// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "CPP_FirstPersonGameMode.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTeamMessageSendtDelegate, FString, PlayerName, FString, Message);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetWaypoint, FString, waypointTag, FString, target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeOnScreenMessage, FString, newText, float, time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetWaypoint, FString, waypointTag, AActor*, target);

/**
 * 
 */

UCLASS()
class BREACH_API ACPP_FirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ACPP_FirstPersonGameMode(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void CreateWaypoint(AActor *actor, FString tag, FVector waypointOffset);
	
	UFUNCTION(BlueprintCallable)
	void RemoveWaypoint(FString tag);

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void UnpauseGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
	UUserWidget* WidgetInstance;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TMap<FString, UUserWidget*> WaypointWidgets;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseTemplate;

	UPROPERTY()
	UUserWidget* PauseMenu;

	//These properties are multicast event dispatchers.
	//We want the capability to bind to this event so we have BlueprintAssignable
	//We want the capability to call this event so we have BlueprintCallable
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FChangeOnScreenMessage ChangeOnScreenMessage;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FSetWaypoint SetWaypoint;

};
