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

bool AMrBoom::IsActivated(APlayerUnit* target){
	auto distance = (this->GetActorLocation() - target->GetActorLocation()).Size();
	
	return (distance <= visionRange);
}

