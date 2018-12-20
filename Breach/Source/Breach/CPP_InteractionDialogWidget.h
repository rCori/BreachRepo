// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_InteractionDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class BREACH_API UCPP_InteractionDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitializeDialogSet(FString dialogJsonFile, FString dialogKey);

	UFUNCTION()
	void AdvanceDialog();

	UFUNCTION()
	bool DialogIsFinished();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<FString> DisplayStrings;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	uint8 currPosition;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FString currDisplay;

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
