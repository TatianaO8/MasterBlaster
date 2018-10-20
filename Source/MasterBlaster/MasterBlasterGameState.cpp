// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterBlasterGameState.h"

#include "BaseUnit.h"

void AMasterBlasterGameState::AddUnit(ABaseUnit* unit) {
	PlayerTeam.Add(unit);
}


