// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "UnrealMathUtility.h"


// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mapWidth = 10;
	ceilingHeight = 10;
	tileSize = 128;
	slope = 15;
}


//Private Functions
void ALevelGenerator::GetTileSpawnLocation(const ABaseTile* previousTile, FVector &location, bool &canChangeDirection) {
	if (previousTile->GetActorRotation().Pitch != 0) {
		location.X = previousTile->GetActorLocation().X + tileSize * FMath::Cos(slope * pi / 180);
		canChangeDirection = false;
	}
	else{
		location.X = previousTile->GetActorLocation().X + tileSize;
		canChangeDirection = true;
	}
}
void ALevelGenerator::GetTileSpawnRotation(const ABaseTile* previousTile, FRotator &rotation, bool canChangeDirection) {
	float previousRotation = previousTile->GetActorRotation().Pitch;
	bool goUp = FMath::RandRange(1, 10) <= 5; //50 / 50 chance to go up or down
	if (!canChangeDirection) {
		rotation.Pitch = previousRotation;
	}
	else if (goUp) {
		rotation.Pitch = slope;
	}
	else {
		rotation.Pitch = -slope;
	}

}

void ALevelGenerator::GenerateFloor() {
	float currElevation = 0;
	bool canChangeDirection;

	//Generate Floor
	//The root tile for the whole map goes at 0,0,0 with no rotations
	ABaseTile* rootTile = GetWorld()->SpawnActor<ABaseTile>(tile, FVector(0, 0, 0), FRotator(0, 0, 0), FActorSpawnParameters());
	floor.Add(rootTile);

	for (int i = 1; i < mapWidth; i++) {
		FVector location(i * 128, 0, currElevation);
		FRotator rotation(0, 0, 0);
		FActorSpawnParameters spawnInfo;

		GetTileSpawnLocation(floor[i - 1], location, canChangeDirection);

		//Determine deltaElevation
		bool changeElevation = FMath::RandRange(1, 10) <= 2; //20% chance to change elevation
		if (changeElevation) {
			GetTileSpawnRotation(floor[i - 1], rotation, canChangeDirection);
			currElevation += tileSize * FMath::Sin(rotation.Pitch * pi / 180);
		}
		ABaseTile* newTile = GetWorld()->SpawnActor<ABaseTile>(tile, location, rotation, spawnInfo);

		floor.Add(newTile);
	}
}
void ALevelGenerator::GenerateCeiling() {
	float currElevation = ceilingHeight * 128;
	bool canChangeDirection;

	//Generate Floor
	//The root tile for the whole map goes at 0,0,0 with no rotations
	ABaseTile* rootTile = GetWorld()->SpawnActor<ABaseTile>(tile, FVector(0, 0, currElevation), FRotator(0, 0, 0), FActorSpawnParameters());
	ceiling.Add(rootTile);

	for (int i = 1; i < mapWidth; i++) {
		FVector location(i * 128, 0, currElevation);
		FRotator rotation(0, 0, 0);
		FActorSpawnParameters spawnInfo;

		GetTileSpawnLocation(ceiling[i - 1], location, canChangeDirection);

		//Determine deltaElevation
		bool changeElevation = FMath::RandRange(1, 10) <= 2; //20% chance to change elevation
		if (changeElevation) {
			GetTileSpawnRotation(ceiling[i - 1], rotation, canChangeDirection);
			currElevation += tileSize * FMath::Sin(rotation.Pitch * pi / 180);
		}
		ABaseTile* newTile = GetWorld()->SpawnActor<ABaseTile>(tile, location, rotation, spawnInfo);

		ceiling.Add(newTile);
	}
}
void ALevelGenerator::GenerateMap() {
	GenerateFloor();
	GenerateCeiling();
}


// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay(){
	Super::BeginPlay();
	GenerateMap();
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

