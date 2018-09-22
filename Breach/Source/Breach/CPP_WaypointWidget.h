// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WaypointWidget.generated.h"

/**
 * 
 */

UCLASS()
class BREACH_API UCPP_WaypointWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	AActor* AttachActor;
	
	UPROPERTY(BlueprintReadWrite)
	FVector LocationOffset;

};
