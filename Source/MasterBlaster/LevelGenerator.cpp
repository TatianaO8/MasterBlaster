// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "CombatMap.h"
#include "Room.h"


// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numRooms = 5;

}

void ALevelGenerator::GenerateLevel() {
	ACombatMap* map = GetWorld()->SpawnActor<ACombatMap>(FVector(0, 0, 0), FRotator(0, 0, 0), FActorSpawnParameters());

	int deltaX = 0;
	for (int i = 0; i < numRooms; i++) {
		//Room position
		FVector location(deltaX, 0, 0);
		FRotator rotation(0, 0, 0);
		FActorSpawnParameters spawnInfo;

		//Spawn Room
		map->AddRoom( GetWorld()->SpawnActor<ARoom>(rooms[0], location, rotation, spawnInfo));

		deltaX += testRoom->GetRoomWidthPixels();
	}

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay(){
	Super::BeginPlay();
	
	GenerateLevel();
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

