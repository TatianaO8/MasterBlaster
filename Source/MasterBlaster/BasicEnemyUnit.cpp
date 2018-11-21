// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"


void ABasicEnemyUnit::BeginPlay() {
	Super::BeginPlay();

	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	teamIndex = gameState->RegisterEnemyUnit(this);
}

//override from BaseUnit
void ABasicEnemyUnit::BeginTurn() {
	EmptyActionPoints();
}


void ABasicEnemyUnit::FireShot(){

}

void ABasicEnemyUnit::Die(){
	Super::Die();
	gameState->UnregisterEnemyUnit(teamIndex);
	Destroy();
}

