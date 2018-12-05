// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectileEvil.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"
#include "PlayerUnit.h"

#include "GenericPlatformMath.h"

float ABasicEnemyUnit::ClosestTargetDistance(){
	float minDistance = 10000000;

	for (auto unit : gameState->GetPlayerTeam()) {
		auto distance = (this->GetActorLocation() - unit->GetActorLocation()).Size();
		if (distance < minDistance) {
			minDistance = distance;
		}
	}

	return minDistance;
}

void ABasicEnemyUnit::BeginPlay() {
	Super::BeginPlay();

	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	teamIndex = gameState->RegisterEnemyUnit(this);

	Activated = false;
}
//override from BaseUnit
void ABasicEnemyUnit::BeginTurn() 
{
	Super::BeginTurn();
	RefreshActionPoints();
	bCanBeDamaged = false;
	EmptyActionPoints();

}

bool ABasicEnemyUnit::ShouldMove(){
	return (ClosestTargetDistance() > MoveRange * 1.25);
}

FVector ABasicEnemyUnit::PickMoveDestination(){
	auto rand = FGenericPlatformMath::SRand();
	FVector MoveDestination = GetActorLocation() + rand * FVector(-MoveRange, 0, 0);


	return MoveDestination;
}

APlayerUnit* ABasicEnemyUnit::AquireTarget() {
	float minDistance = 2560;
	APlayerUnit* closestUnit = nullptr;

	for (auto playerUnit : gameState->GetPlayerTeam()) {

		if (playerUnit == nullptr)
			continue;

		auto unitLocation = playerUnit->GetActorLocation();
		auto distance = (this->GetActorLocation() - unitLocation).Size();

		if (distance <= minDistance) {
			minDistance = distance;
			closestUnit = Cast<APlayerUnit>(playerUnit);
		}

	}

	return closestUnit;
}

bool ABasicEnemyUnit::IsActivated(){
	return Activated;

}

bool ABasicEnemyUnit::CheckActivation(){
	//auto distance = (this->GetActorLocation() - target->GetActorLocation()).Size();

	Activated = ClosestTargetDistance() <= 2.0 * MoveRange;

	return Activated;
}


void ABasicEnemyUnit::Die(){
	Super::Die();
	gameState->UnregisterEnemyUnit(this);
	Destroy();
}

