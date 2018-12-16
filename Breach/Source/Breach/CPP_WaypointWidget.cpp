// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_WaypointWidget.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogWaypointWidget, Display, All);
void UCPP_WaypointWidget::NativeConstruct()
{
	// Do some custom setup

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UCPP_WaypointWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Do your custom tick stuff here

	if(AttachActor != nullptr){
		if(GetWorld() != nullptr){
			const FVector inputLocation = AttachActor->GetActorLocation() + LocationOffset;
			FVector2D outLocation;
			UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(),inputLocation,outLocation,false);
			int sizeX, sizeY;
			GetWorld()->GetFirstPlayerController()->GetViewportSize(sizeX,sizeY);
			//UE_LOG(LogWaypointWidget, Display,TEXT("sizeX: %f"),(float)sizeX);
			//UE_LOG(LogWaypointWidget, Display,TEXT("sizeY: %f"),(float)sizeY);

			auto xPos = FMath::Clamp(outLocation.X, 0.0f, (float)(sizeX-50.0));
			auto yPos = FMath::Clamp(outLocation.Y, 0.0f, (float)(sizeY-50.0));

			FVector2D finalLocation = FVector2D(xPos,yPos);
			//UE_LOG(LogWaypointWidget, Display,TEXT("finalLocation.X: %f"),(float)finalLocation.X);
			//UE_LOG(LogWaypointWidget, Display,TEXT("finalLocation.Y: %f"),(float)finalLocation.Y);

			SetPositionInViewport(finalLocation);
		}
	}
}