// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSCAR.generated.h"

class UBoxComponent;
class ACPP_FirstPersonCharacter;

UCLASS()
class BREACH_API APickupSCAR : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSCAR();

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

	UFUNCTION(BlueprintImplementableEvent)
	void BindToCharacterIsUsing(ACPP_FirstPersonCharacter* firstPersonCharacter,bool bindTo);

	UFUNCTION(BlueprintCallable)
	void AwardSCAR(ACPP_FirstPersonCharacter* firstPersonCharacter);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* GunMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* genericInGameEvent;
};
