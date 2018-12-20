// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_InteractionDialogWidget.h"
#include "GameFramework/Actor.h"
#include "InteractArea.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIsInRangeInteract, bool, IsInRange);

class UBoxComponent;
class UUserWidget;

UENUM(BlueprintType)
enum class InteractionState :uint8 
{
	begin, 
	middle,
	end 
};

UCLASS()
class BREACH_API AInteractArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetIsInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void SetNotInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void DoInteraction();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BlueprintsToAssign")
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FIsInRangeInteract IsInRangeInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintsToAssign")
	TSubclassOf<UCPP_InteractionDialogWidget> InteractionDialogWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "JSONInfo")
	FString jsonFile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "JSONInfo")
	FString jsonDialogNode;

	UPROPERTY()
	UCPP_InteractionDialogWidget* InteractionDialog;

private:
	InteractionState interactionState;
};
