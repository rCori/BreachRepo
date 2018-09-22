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

	UFUNCTION(BlueprintCallable)
	void CreateWaypoint(AActor *actor, FString tag, FVector waypointOffset);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetTemplate;
 
	UPROPERTY()
	UUserWidget* WidgetInstance;

};
