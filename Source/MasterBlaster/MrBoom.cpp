// Fill out your copyright notice in the Description page of Project Settings.

#include "MrBoom.h"
#include "PlayerUnit.h"
#include "MasterBlasterGameState.h"

AMrBoom::AMrBoom(){
	hasFired = false;
	visionRange = 2560;

	HealthPercentage = 1.0f;
	PrimaryActorTick.bCanEverTick = true;
	FullHealth = 150.0f;
	Health = FullHealth;
}

float AMrBoom::GetHealth() {
	return Health;
}

void AMrBoom::BeginPlay() {
	GameState = GetWorld()->GetGameState<AMasterBlasterGameState>();

	GameState->RegisterMrBoom(this);
}

APlayerUnit* AMrBoom::AquireTarget(){
	float minDistance = 1000000;
	APlayerUnit* closestUnit = nullptr;
	for (auto playerUnit : GameState->GetPlayerTeam()) {
		
		if (playerUnit == nullptr) continue;

		auto unitLocation = playerUnit->GetActorLocation();
		auto distance = (this->GetActorLocation() - unitLocation).Size();
		if (distance < minDistance) {
			minDistance = distance;
			closestUnit = Cast<APlayerUnit>(playerUnit);
		}
	}

	return closestUnit;
}

bool AMrBoom::IsActivated(){
	//auto distance = (this->GetActorLocation() - target->GetActorLocation()).Size();
	float minDistance = 10000000;

	for (auto unit : GameState->GetPlayerTeam()) {
		auto distance = (this->GetActorLocation() - unit->GetActorLocation()).Size();
		if ( distance < minDistance) {
			minDistance = distance;
		}
	}

	return (minDistance <= visionRange);
}

float AMrBoom::GetHealthPercentage(){
	return HealthPercentage;
}

FText AMrBoom::GetHealthIntText()
{
	int32 hp = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString hps = FString::FromInt(hp);
	FString healthHUD = hps + FString(TEXT("%"));
	FText hpText = FText::FromString(healthHUD);
	return hpText;
}

void AMrBoom::UpdateHealth(float HealthChange)
{ 
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

float AMrBoom::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	return DamageAmount;
}

void AMrBoom::Tick(float DeltaTime){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Oh death"));
	Super::Tick(DeltaTime);

	if (Health <= 0) {
		Die();
	}
}

void AMrBoom::Die(){
	GetWorld()->DestroyActor(this);
}