// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DummyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UDummyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BREACH_API IDummyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void DummyInterfaceFunction();
	
};
