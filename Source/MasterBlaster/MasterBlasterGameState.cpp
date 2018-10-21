// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterBlasterGameState.h"

#include "BaseUnit.h"

AMasterBlasterGameState::AMasterBlasterGameState() {
	activeUnit = 0;
}

void AMasterBlasterGameState::AddUnit(ABaseUnit* unit) {
	PlayerTeam.Add(unit);
}

void AMasterBlasterGameState::SetActiveUnit(int index){
	activeUnit = index;
}

void AMasterBlasterGameState::CycleUnit(){
	activeUnit++;  
	activeUnit %= PlayerTeam.Num();
	//GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("%d"), activeUnit));
}

ABaseUnit* AMasterBlasterGameState::GetActiveUnit() {
	
	return (PlayerTeam.Num() > 0) ? PlayerTeam[activeUnit] : nullptr;
}

int AMasterBlasterGameState::SearchForUnitIndex(ABaseUnit * unit){
	for (int i = 0; i < PlayerTeam.Num(); i++) {
		if (PlayerTeam[i] == unit) {
			return i;
		}
	}
	return 0;
}

int AMasterBlasterGameState::GetPlayerTeamSize(){
	return PlayerTeam.Num();
}


