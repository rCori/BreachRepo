// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_InteractionDialogWidget.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractionDialogWidget, Display, All);

void UCPP_InteractionDialogWidget::NativeConstruct()
{
	UE_LOG(LogTemp,Log,TEXT("UCPP_InteractionDialogWidget NativeConstruct"));
	// Do some custom setup

	const FString JsonFilePath = FPaths::ProjectContentDir() + "/JsonData/InteractionDialog.json";

	FString JsonString; //Json converted to FString
	
	FFileHelper::LoadFileToString(JsonString,*JsonFilePath);
 
	//Displaying the json in a string format inside the output log
	UE_LOG(LogTemp,Log,TEXT("Json String:"));
	UE_LOG(LogTemp,Log,TEXT("%s"), *JsonString);

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UCPP_InteractionDialogWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}