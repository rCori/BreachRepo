// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_InteractionDialogWidget.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractionDialogWidget, Display, All);

void UCPP_InteractionDialogWidget::AdvanceDialog()
{
	if(DisplayStrings.Num() != 0 && currPosition < DisplayStrings.Num()){
		currPosition++;
		currDisplay = DisplayStrings[currPosition];
	}
}


bool UCPP_InteractionDialogWidget::DialogIsFinished(){
	return (currPosition + 1) == DisplayStrings.Num();
}


void UCPP_InteractionDialogWidget::NativeConstruct()
{

	/*
	UE_LOG(LogTemp,Log,TEXT("UCPP_InteractionDialogWidget NativeConstruct"));
	// Do some custom setup

	const FString JsonFilePath = FPaths::ProjectContentDir() + "/JsonData/InteractionDialog.json";

	FString JsonString; //Json converted to FString
	
	FFileHelper::LoadFileToString(JsonString,*JsonFilePath);
 
	//Displaying the json in a string format inside the output log
	UE_LOG(LogTemp,Log,TEXT("Json String:"));
	UE_LOG(LogTemp,Log,TEXT("%s"), *JsonString);
	*/

	currPosition = 0;

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UCPP_InteractionDialogWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}


void UCPP_InteractionDialogWidget::InitializeDialogSet(FString dialogJsonFile, FString dialogKey)
{
	const FString JsonFilePath = FPaths::ProjectContentDir() + dialogJsonFile;

	FString JsonString; //Json converted to FString
	
	FFileHelper::LoadFileToString(JsonString,*JsonFilePath);

	//Create a json object to store the information from the json string
	//The json reader is used to deserialize the json object later on
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
 
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		//The person "object" that is retrieved from the given json file
		TSharedPtr<FJsonObject> MyInteraction = JsonObject->GetObjectField("InteractionDialog")->GetObjectField(dialogKey);
		TArray<TSharedPtr<FJsonValue>> DialogArray = MyInteraction->GetArrayField("DisplayText");
		DisplayStrings.Empty();
		for(int i = 0; i < DialogArray.Num(); i++){
			DisplayStrings.Push(DialogArray[i]->AsString());
		}
	}
	currPosition = 0;
	currDisplay = DisplayStrings[currPosition];
}