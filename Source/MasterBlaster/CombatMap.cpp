// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatMap.h"
#include "BaseUnit.h"
#include "BasicEnemyUnit.h"
#include "BasicEnemyUnit.h"

#include "Room.h"

// Sets default values
ACombatMap::ACombatMap(){

}


// Called when the game starts or when spawned
void ACombatMap::BeginPlay(){
	Super::BeginPlay();
}

ARoom* ACombatMap::GetSpawnRoom() {
	return (rooms.Num() > 0) ? rooms[0] : nullptr;
}

ARoom* ACombatMap::GetLastRoom(){
	return (rooms.Num() > 0) ? rooms[rooms.Num()-1] : nullptr;
}

//Public Functions
void ACombatMap::AddRoom(ARoom* room) {
	rooms.Add(room);
}

void ACombatMap::SpawnEnemies(TSubclassOf<ABasicEnemyUnit> EnemyUnitBP){
	for (auto x : rooms) {
		x->SpawnEnemies(EnemyUnitBP);
	}
}
