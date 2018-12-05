// Fill out your copyright notice in the Description page of Project Settings.

#include "CoverBlock.h"

void ACoverBlock::Die(){
	Destroy();
}

ACoverBlock::ACoverBlock(){
	Health = 100.f;
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
	if (Health <= 0.f) {
		Die();
	}
}

