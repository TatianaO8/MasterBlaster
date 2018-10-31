// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"


void ABasicEnemyUnit::BeginPlay() {
	Super::BeginPlay();

	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	gameState->RegisterEnemyUnit(this);
}

