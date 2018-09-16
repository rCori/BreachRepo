// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTestInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UMyTestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BREACH_API IMyTestInterface
{
	GENERATED_BODY()



public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void MyFunctionToImplement();
	
};
