// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterBlasterGameState.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"
#include "BaseUnit.h"
#include "BasicEnemyUnit.h"

AMasterBlasterGameState::AMasterBlasterGameState() {
	//index into the playerteam array
	activeUnit = 0;
	
	IsPlayerTurn = true;

	GameOver = false;

}

int AMasterBlasterGameState::RegisterPlayerUnit(ABaseUnit* unit) {
	PlayerTeam.Add(unit);
	return PlayerTeam.Num() - 1;
}

int AMasterBlasterGameState::RegisterEnemyUnit(ABaseUnit * unit){
	EnemyTeam.Add(unit);
	return EnemyTeam.Num() - 1;
}

void AMasterBlasterGameState::UnregisterPlayerUnit(int index){
	PlayerTeam.RemoveAt(index, 1, true);

	//To deselect current unit, cycle to the next
	CycleUnit();
}

void AMasterBlasterGameState::UnregisterEnemyUnit(int index){
	EnemyTeam.RemoveAt(index, 1, true);
}

void AMasterBlasterGameState::SetActiveUnit(int index){
	activeUnit = index;
}

void AMasterBlasterGameState::CycleUnit(){
	for (int i = 0; i < PlayerTeam.Num(); i++) {
		activeUnit++;
		activeUnit %= PlayerTeam.Num();
		if (PlayerTeam[activeUnit]->ActionPoints > 0) {
			return;
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("%d"), activeUnit));
}

ABaseUnit* AMasterBlasterGameState::GetActiveUnit() {
	if (PlayerTeam.Num() <= activeUnit)
		return nullptr;

	return (PlayerTeam.Num() > 0) ? PlayerTeam[activeUnit] : nullptr;
}

TArray<ABaseUnit*> AMasterBlasterGameState::GetPlayerTeam(){
	return PlayerTeam;
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

bool AMasterBlasterGameState::GetIsPlayerTurn(){
	return IsPlayerTurn;
}

void AMasterBlasterGameState::BeginEnemyTurn(){
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Begin Enemy Turn")));
	IsPlayerTurn = false;
	count = 0;
	
	//Refesh Team's AP
	for (auto x : EnemyTeam) {
		if (x == nullptr) continue;

		x->BeginTurn();		
	}
}

void AMasterBlasterGameState::BeginPlayerTurn(){
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Begin Player Turn")));
	for (auto x : PlayerTeam) {
		x->BeginTurn();
	}
	IsPlayerTurn = true;
}

bool AMasterBlasterGameState::PlayerTurnUpdate(){
	bool turnOverFlag = true;
	for (auto x : PlayerTeam) {
		if (x == nullptr) continue;

		if (x->GetActionPoints() > 0 || x->GetIsMoving()) {
			turnOverFlag = false;
			break;
		}
	}

	return turnOverFlag;
}

bool AMasterBlasterGameState::EnemyTurnUpdate(){
	bool turnOverFlag = true;
	for (auto x : EnemyTeam) {
		if (x == nullptr) continue;

		if (x->GetActionPoints() > 0) {
			turnOverFlag = false;
			break;
		}
	}

	return turnOverFlag;
}

//Game Over, Next level, player's turn, enemy's turn
void AMasterBlasterGameState::UpdateGameState() {
	// if there are no more units, game over
	if (combatStarted == false) {
		return;
	}
		
	if (PlayerTeam.Num() == 0) {
		//gameOver = 1;
		GameOver = true;
	}
	//if none of the units have actions, enemy's turn
	if (IsPlayerTurn) {
		PlayerTurnUpdate();
	}
	else {
		EnemyTurnUpdate();
	}
}

void AMasterBlasterGameState::StartCombat(){
	combatStarted = true;
}

bool AMasterBlasterGameState::GetCombatStarted(){
	return combatStarted;
}

