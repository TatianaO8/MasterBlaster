// Fill out your copyright notice in the Description page of Project Settings.

#include "CoverBlock.h"



ACoverBlock::ACoverBlock(){
	Health = 100.f;
	FullHealth = 100.f;
	HealthPercentage = 1.0f;
	PrimaryActorTick.bCanEverTick = true;
}

float ACoverBlock::GetHealthPercentage(){
	return HealthPercentage;
}

FText ACoverBlock::GetHealthIntText()
{
	int32 hp = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString hps = FString::FromInt(hp);
	FString healthHUD = hps + FString(TEXT("%"));
	FText hpText = FText::FromString(healthHUD);
	return hpText;
}

void ACoverBlock::UpdateHealth(float HealthChange)
{ 
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

float ACoverBlock::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	return DamageAmount;
}

void ACoverBlock::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Okay this one is working what the heck"));

	if (Health <= 0) {
		Die();
	}
}

void ACoverBlock::Die(){
	GetWorld()->DestroyActor(this);
}