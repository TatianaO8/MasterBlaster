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

void AMasterBlasterGameState::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	//This tick function doesn't seem to work.
	
	//GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("Tick")));
	//UpdateGameState();
}

void AMasterBlasterGameState::RegisterPlayerUnit(ABaseUnit* unit) {
	PlayerTeam.Add(unit);
}

void AMasterBlasterGameState::RegisterEnemyUnit(ABaseUnit * unit){
	EnemyTeam.Add(unit);
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

TArray<ABaseUnit*> AMasterBlasterGameState::GetPlayerTeam()
{
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
		count++;
		if(count<3)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Enemy: %d"), count));
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

void AMasterBlasterGameState::PlayerTurnUpdate(){
	bool turnOverFlag = true;
	for (auto x : PlayerTeam) {
		if (x->GetActionPoints() > 0) {
			turnOverFlag = false;
			break;
		}
	}

	if (turnOverFlag) {
		BeginEnemyTurn();
	}
}

void AMasterBlasterGameState::EnemyTurnUpdate(){
	bool turnOverFlag = true;
	for (auto x : EnemyTeam) {
		if (x->GetActionPoints() > 0) {
			turnOverFlag = false;
			break;
		}
	}

	if (turnOverFlag) {
		BeginPlayerTurn();
	}
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

