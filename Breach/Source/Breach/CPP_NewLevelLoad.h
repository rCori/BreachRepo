// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "CPP_NewLevelLoad.generated.h"


UCLASS()
class BREACH_API ACPP_NewLevelLoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_NewLevelLoad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FString LevelName;
	
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Character")
	TSubclassOf<AActor> FirstPersonCharacterClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LoadLevelWidget;
};
