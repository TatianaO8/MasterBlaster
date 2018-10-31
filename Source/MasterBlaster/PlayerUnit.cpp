// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUnit.h"

#include "MasterBlasterGameState.h"

void APlayerUnit::BeginPlay() {
	Super::BeginPlay();
	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	gameState->RegisterPlayerUnit(this);
	MyTeamIndex = gameState->GetPlayerTeamSize() - 1;

}

