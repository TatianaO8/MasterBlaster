// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Engine.h"

const FName ABaseUnit::FireRightBinding("FireRight");
const FName ABaseUnit::FireForwardBinding("FireForward");

// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


	/*
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(0.f, -100.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	*/
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	
	bCanBeDamaged = true;
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Set up gameplay key bindings
	PlayerInputComponent->BindAxis(FireRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);

}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UnitLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UnitLocation.ToString());

	// Create fire direction vector
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const FVector FireDirection = FVector(FireRightValue, 0.f, FireForwardValue);

	// Try and fire a shot
	FireShot(FireDirection);
}



float ABaseUnit::GetHealth()
{
	return HealthPercentage;
}

FText ABaseUnit::GetHealthIntText()
{
	int32 hp = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString hps = FString::FromInt(hp);
	FString healthHUD = hps + FString(TEXT("%"));
	FText hpText = FText::FromString(healthHUD);
	return hpText;
}

void ABaseUnit::SetDamageState()
{
	bCanBeDamaged = true;
}

float ABaseUnit::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	return DamageAmount;
}

void ABaseUnit::UpdateHealth(float HealthChange)
{
	Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

void ABaseUnit::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<AProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABaseUnit::ShotTimerExpired, FireRate);

			bCanFire = false;
		}
	}
}

void ABaseUnit::ShotTimerExpired()
{
	bCanFire = true;
}