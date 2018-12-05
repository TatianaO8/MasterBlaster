// Fill out your copyright notice in the Description page of Project Settings.

#include "MrBoom.h"
#include "PlayerUnit.h"
#include "MasterBlasterGameState.h"

AMrBoom::AMrBoom(){
	hasFired = false;
	visionRange = 2560;

	FullHealth = 150.0f;
	Health = FullHealth;
}

float AMrBoom::GetHealth() {
	return Health;
}

void AMrBoom::BeginPlay() {
	Super::BeginPlay();
	GameState = GetWorld()->GetGameState<AMasterBlasterGameState>();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("MrBoom called"));

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

