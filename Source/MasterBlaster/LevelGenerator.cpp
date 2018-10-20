// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "Room.h"
#include "CombatMap.h"
#include "BaseUnit.h"
#include "PlayerUnit.h"

#include "GenericPlatformMath.h"

/// ctors

// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numRooms = 5;
	seed = FGenericPlatformMath::Rand();

	DefaulPlayerTeamSize = 3;

	return;
}

/// Private Functions
void ALevelGenerator::SpawnCombatMap() {
	FVector mapSpawnLocation(0, 0, 1152);
	FRotator mapSpawnRotation(0, 0, 0);

	//Spawn Combat Map
	map = GetWorld()->SpawnActor<ACombatMap>(mapSpawnLocation, mapSpawnRotation, FActorSpawnParameters());
	
	//Place Spawn Room
	ARoom* spawnRoom = GetWorld()->SpawnActor<ARoom>(spawnRoomBP, mapSpawnLocation, mapSpawnRotation, FActorSpawnParameters());
	map->AddRoom(spawnRoom);
}

//Returns the subset of the target room library that can be placed based on the previous room in the map.
TArray<TSubclassOf<ARoom>> ALevelGenerator::GetValidRooms(ARoom * previousRoom, TArray<TSubclassOf<ARoom>> targetLibrary){
	TArray<TSubclassOf<ARoom>> validRooms;
	int validRoomCount = 0;
	
	for (int i = 0; i < targetLibrary.Num(); i++) {
		ARoom* tempRoom = GetWorld()->SpawnActor<ARoom>(targetLibrary[i], FVector(0, -100, 0), FRotator(0, 0, 0), FActorSpawnParameters());
		if (previousRoom->CanConnectTo(tempRoom)) {
			validRooms.Add(targetLibrary[i]);
		}
		tempRoom->Destroy();
	}
	return validRooms;
}


//Selects and returns a room from the Room Library
TSubclassOf<ARoom> ALevelGenerator::SelectRoom(ARoom* previousRoom, TArray<TSubclassOf<ARoom>> targetLibrary) {
	//Hashmap of valid rooms and their library index
	auto validRooms = GetValidRooms(previousRoom, targetLibrary);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Valid Rooms: %d"), validRooms.Num()));

	float seededRandomNumber = FGenericPlatformMath::SRand();
	int roomSelection = 0;
	
	//Convert float to int in range 0 -> validRooms.Num();
	roomSelection = (seededRandomNumber * 10);
	roomSelection = roomSelection % validRooms.Num();

	return validRooms[roomSelection];
}



void ALevelGenerator::SpawnRoom(TSubclassOf<ARoom> room, int xPosition) {
	//Room position
	FVector location(xPosition, 0, 1152);
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters spawnInfo;

	//Spawn Room
	ARoom* newRoom = GetWorld()->SpawnActor<ARoom>(room, location, rotation, spawnInfo);
	map->AddRoom(newRoom);
}


void ALevelGenerator::PlaceRooms(ARoom* root){
	

	//Where the next room should be placed.
	int xPosition = root->GetRoomWidthPixels();
	ARoom* previousRoom = root;

	//Place middle rooms of map
	for (int i = 0; i < numRooms; i++) {
		//Select room
		auto selectedRoom = SelectRoom(previousRoom, RoomLibrary);

		//Spawn and save reference to created actor
		SpawnRoom(selectedRoom, xPosition);

		//Update spawn position for next room
		previousRoom = map->GetLastRoom();
		xPosition += previousRoom->GetRoomWidthPixels();
	}

	//Place ending room
	auto selectedRoom = SelectRoom(previousRoom, EndRoomLibrary);
	SpawnRoom(selectedRoom, xPosition);

}

void ALevelGenerator::SpawnPlayerTeam(){
	int x = 0;
	for (int i = 0; i < DefaulPlayerTeamSize; i++) {
		FVector location(128 + i*128, 0, 500);
		FRotator rotation(0, 0, 0);
		APlayerUnit* unit = GetWorld()->SpawnActor<APlayerUnit>(PlayerUnitBP, location, rotation);
		//GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("Spawn")));
	}
}

void ALevelGenerator::GenerateLevel() {
	//Seed the random number generator
	FGenericPlatformMath::SRandInit(seed);

	//Spawns the CombatMap and puts down the spawn room.
	SpawnCombatMap();

	//Handled by the level-gen blueprint
	PlaceRooms(map->GetSpawnRoom());

	//Spawns player units in spawn room
	SpawnPlayerTeam();

	//Spawns Enemy Units in each room.
	//SpawnEnemyTeam();
}

bool ALevelGenerator::ValidateEditorInput(){
	//Validate Spawn Room
	if (spawnRoomBP) {
		;
	}
	else {
		return false;
	}

	if (RoomLibrary.Num() == 0) return false;
	
	//Validate Room Library
	for (TSubclassOf<ARoom> room : RoomLibrary) {
		if (room) {
			continue;
		} 
		else {
			return false;
		}
	}

	if (EndRoomLibrary.Num() == 0) return false;

	//Validate End rooms
	for (TSubclassOf<ARoom> room : EndRoomLibrary) {
		if (room) {
			continue;
		}
		else {
			return false;
		}
	}

	return true;
}




/// Protected Functions

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay(){
	Super::BeginPlay();

	if (!ValidateEditorInput()) {
		GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("ERROR: Please properly set up the level generator in the editor.")));
		return;
	}
	
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

