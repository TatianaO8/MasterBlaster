// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterBlasterGameState.h"

#include "BaseUnit.h"

AMasterBlasterGameState::AMasterBlasterGameState() {
	//index into the playerteam array
	activeUnit = 0;
	
	// turn = 0, player turn
	// turn = 1, enemy turn
	turn = 0;

	//DO THIS ON A BLUEPRINT
	// gameOver = 0, game is NOT over
	// gameOver = 1, game is over & display game over menu
	gameOver = 0;

}

void AMasterBlasterGameState::PlayerTurn(int turn)
{
	// if there are no more units, game over
	if (GetPlayerTeamSize() == 0) {
		gameOver = 1;
	}

	//if none of the units have actions, enemy's turn
	if (GetActionPoints() == 0) {
		turn = 1;
		//send signal to enemy AI controller
	}
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


