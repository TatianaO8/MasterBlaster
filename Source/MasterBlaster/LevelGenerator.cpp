// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "CombatMap.h"
#include "Room.h"


// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numRooms = 5;
	return;
}

int ALevelGenerator::SelectRoom() {
	int roomSelection = -1;



	return 1;
}

void ALevelGenerator::SpawnRoom(int roomNum, int &x) {
	//Room position
	FVector location(x, 0, 0);
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters spawnInfo;

	//Spawn Room
	ARoom* newRoom = GetWorld()->SpawnActor<ARoom>(rooms[0], location, rotation, spawnInfo);
	map->AddRoom(newRoom);
	
	x += newRoom->GetRoomWidthPixels();

	return;
}

void ALevelGenerator::GenerateLevel() {
	
	map = GetWorld()->SpawnActor<ACombatMap>(FVector(0, 0, 0), FRotator(0, 0, 0), FActorSpawnParameters());

	int deltaX = 0;
	for (int i = 0; i < numRooms; i++) {
		int roomNum = SelectRoom();
		if (roomNum == -1) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Unable to select room. Aborting level generation"));
			}
			return;
		}
		SpawnRoom(roomNum, deltaX);
	
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

