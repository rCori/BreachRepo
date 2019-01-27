// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieEnemyCharacter.h"
#include "PlayerHealthComponent.h"
#include "CPP_FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogAttackRange);
DEFINE_LOG_CATEGORY(HitByFPSProjectile);


// Sets default values
AZombieEnemyCharacter::AZombieEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 // set default pawn class to our Blueprinted character
     static ConstructorHelpers::FClassFinder<AActor> FirstPersonProjectileClassTemp(TEXT("/Game/BlueprintSource/FirstPersonProjectile"));
     if (FirstPersonProjectileClassTemp.Class != NULL)
     {
         FirstPersonProjectileClass = FirstPersonProjectileClassTemp.Class;
     }

	AttackRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	AttackRange->SetupAttachment(RootComponent);
	AttackRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(GetMesh());
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//ECC_GameTraceChannel1 = "Projectile"
	HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,ECollisionResponse::ECR_Block);
	//ECC_GameTraceChannel2 = "EnemyLOS"
	HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2,ECollisionResponse::ECR_Block);
	

	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,ECollisionResponse::ECR_Block);

	walkSpeed = 200.0;
	health = 100.0;
	isAttackRange = false;
	firstPersonCharacter = nullptr;

	//Assign the Event Hit delegate
	OnActorHit.AddDynamic(this, &AZombieEnemyCharacter::OnHit);

}

// Called when the game starts or when spawned
void AZombieEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemyCharacter::SetIsInRange);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AZombieEnemyCharacter::SetNotInRange);

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	attackCooldown = 0.0;
}

// Called every frame
void AZombieEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(attackCooldown > 0.0){
		attackCooldown -= DeltaTime;
		if(attackCooldown <= 0.0){
			GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
		}
	}

}

// Called to bind functionality to input
void AZombieEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AZombieEnemyCharacter::SetIsInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACPP_FirstPersonCharacter* playerCharacter = Cast<ACPP_FirstPersonCharacter>(OtherActor);
	if(playerCharacter != nullptr){
		UE_LOG(LogAttackRange, Warning, TEXT("Zombie is in range"));
		firstPersonCharacter = playerCharacter;
		isAttackRange = true;
	} 
}

void AZombieEnemyCharacter::SetNotInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPP_FirstPersonCharacter* playerCharacter = Cast<ACPP_FirstPersonCharacter>(OtherActor);
	if(playerCharacter != nullptr){
		UE_LOG(LogAttackRange, Warning, TEXT("Zombie left range"));
		firstPersonCharacter = nullptr;
		isAttackRange = false;
	}
}

// Attempt an attack if the player is within bounds
void AZombieEnemyCharacter::DoAttack()
{
	if(attackCooldown > 0.0){
		return;
	}
	UE_LOG(LogAttackRange, Warning, TEXT("Zombie Attack!"));
	if(firstPersonCharacter != nullptr && isAttackRange){
		UE_LOG(LogAttackRange, Warning, TEXT("firstPersonCharacterRef is valid and attackInRange is true"));
		//TSubclassOf<UPlayerHealthComponent> playerHealthClass;
		//UPlayerHealthComponent* healthComponent = Cast<UPlayerHealthComponent>(firstPersonCharacter->GetComponentByClass(playerHealthClass));
		// try and play a firing animation if specified
		if (AttackAnimation != NULL)
		{
			UE_LOG(LogAttackRange, Warning, TEXT("AttackAnimation found"));
			// Get the animation object for zombie character mesh
			// ACharacters have a default mesh and we can get a reference to it with GetMEsh
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				attackCooldown = AnimInstance->Montage_Play(AttackAnimation, 1.f,EMontagePlayReturnType::Duration);
			}
		} else {
			UE_LOG(LogAttackRange, Warning, TEXT("No AttackAnimation set"));
		}
		GetCharacterMovement()->MaxWalkSpeed = 0.0;
		firstPersonCharacter->healthComponent->TakeDamage(5.0f);
	} else {
		if(firstPersonCharacter == nullptr){
			UE_LOG(LogAttackRange, Warning, TEXT("firstPersonCharacterRef is null"));
		}

		if(!isAttackRange){
			UE_LOG(LogAttackRange, Warning, TEXT("attackInRange is false."));
		}
	}

}


bool AZombieEnemyCharacter::IsReadyToAttack()
{
	return (attackCooldown <= 0.0);
}

void AZombieEnemyCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(HitByFPSProjectile, Warning, TEXT("Zombie onHit"));
	UE_LOG(HitByFPSProjectile, Warning, TEXT("SelfActor was %s"), *SelfActor->GetName());
	UE_LOG(HitByFPSProjectile, Warning, TEXT("OtherActor was %s"), *OtherActor->GetName());
	UE_LOG(HitByFPSProjectile, Warning, TEXT("Hit.GetComponent() was %s"), *Hit.GetComponent()->GetName());
	
	UBoxComponent* SelfActorBoxComponent = Cast<UBoxComponent>(OtherActor);
	if(Hit.GetComponent() == HitBox){
		if(FirstPersonProjectileClass->IsChildOf(OtherActor->StaticClass())){
			OtherActor->Destroy();
			FRotator rotation = FRotator::ZeroRotator;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodParticle, Hit.Location, rotation);
			health -= 30;
			if(health <= 0){
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeParticle, GetActorLocation(), GetActorRotation());
				Destroy();
			}
		}
	}
}