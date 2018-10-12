// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "CombatMap.h"
#include "Room.h"

#include "GenericPlatformMath.h"

/// ctors

// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numRooms = 5;
	seed = FGenericPlatformMath::Rand();
	return;
}

/// Private Functions
void ALevelGenerator::SpawnCombatMap() {
	FVector mapSpawnLocation(0, 0, 1152);
	FRotator mapSpawnRotation(0, 0, 0);

	//Spawn Combat Map
	map = GetWorld()->SpawnActor<ACombatMap>(mapSpawnLocation, mapSpawnRotation, FActorSpawnParameters());

	ARoom* spawnRoom = GetWorld()->SpawnActor<ARoom>(spawnRoomBP, mapSpawnLocation, mapSpawnRotation, FActorSpawnParameters());
	map->AddRoom(spawnRoom);
}

TMap<int, TSubclassOf<ARoom>> ALevelGenerator::GetValidRooms(ARoom * previousRoom){
	TMap<int, TSubclassOf<ARoom>> validRooms;
	int validRoomCount = 0;

	for (int i = 0; i < RoomLibrary.Num(); i++) {
		ARoom* tempRoom = GetWorld()->SpawnActor<ARoom>(RoomLibrary[i], FVector(0, -100, 0), FRotator(0, 0, 0), FActorSpawnParameters());
		if (previousRoom->CanConnectTo(tempRoom)) {
			validRooms.Add(validRoomCount++, RoomLibrary[i]);
		}
		tempRoom->Destroy();
	}
}

int ALevelGenerator::SelectRoom(ARoom* previousRoom) {
	//Hashmap of valid rooms and their library index
	auto validRooms = GetValidRooms(previousRoom);
	
	float seededRandomNumber = FGenericPlatformMath::SRand();
	int roomSelection;
	//Convert float to int in range 0 -> validRooms.Num();
	

	return roomSelection;
}



void ALevelGenerator::SpawnRoom(int roomNumber, int xPosition) {
	//Room position
	FVector location(xPosition, 0, 1152);
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters spawnInfo;

	//Spawn Room
	ARoom* newRoom = GetWorld()->SpawnActor<ARoom>(RoomLibrary[roomNumber], location, rotation, spawnInfo);
	map->AddRoom(newRoom);
	
	
	return;

}


void ALevelGenerator::PlaceRooms(ARoom* root){
	//Where the next room should be placed.
	int xPosition = root->GetRoomWidthPixels();
	ARoom* previousRoom = root;

	for (int i = 0; i < numRooms; i++) {
		//Select room
		int roomNum = SelectRoom(previousRoom);
		
		//Validate Selection
		if (roomNum == -1) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Room Selection Failed."));
			}
			return;
		}

		//Spawn Selection
		SpawnRoom(roomNum, xPosition);
	}
}

void ALevelGenerator::GenerateLevel() {
	//Spawns the CombatMap and puts down the spawn room.
	SpawnCombatMap();

	//Handled by the level-gen blueprint
	PlaceRooms(map->getSpawnRoom());

	//Spawns player units in spawn room
	//SpawnPlayerTeam();

	//Spawns Enemy Units in each room.
	//SpawnEnemyTeam();
}


/// Protected Functions

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay(){
	Super::BeginPlay();

	FGenericPlatformMath::SRandInit(seed);
	GenerateLevel();
}

///Public Functions

// Called every frame
void ALevelGenerator::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

ACombatMap* ALevelGenerator::GetCombatMap(){
	return map;
}

