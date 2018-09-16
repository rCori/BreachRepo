// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_GenericInGameEvent.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCPP_GenericInGameEvent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BREACH_API ICPP_GenericInGameEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void InGameEvent();
	
};
