// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Engine.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	bCanBeDamaged = true;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UnitLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UnitLocation.ToString());

}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

