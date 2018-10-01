// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"

#include "UnrealMathUtility.h"


// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mapWidth = 10;
	ceilingHeight = 10;
	slope = 15;
}


//Private Functions
void GetSpawnPosition(const ABaseTile *previousTile, FVector &location) {
	float pX = previousTile->GetActorLocation().X;
	float pY = previousTile->GetActorLocation().Y;
	float pZ = previousTile->GetActorLocation().Z;
	FRotator pR = previousTile->GetActorRotation();

	if (previousTile->GetActorRotation() == FRotator(0, 0, 0)) {
		location = FVector(pX + 128, 0, pZ);
		return;
	}
	
	
	// Cos/Sin is in radians for some reason

	float nX = pX + (128 * FMath::Cos(pR.Pitch));
	float nZ = pZ + (128 * FMath::Sin(pR.Pitch));
	location = FVector(nX, 0, nZ);
	return;
}
void ALevelGenerator::GenerateMap() {
	//Generate Floor
	float currElevation = 0;
	
	//The root tile for the whole map goes at 0,0,0 with no rotations
	ABaseTile* rootTile = GetWorld()->SpawnActor<ABaseTile>(tile, FVector(0, 0, 0), FRotator(0, 0, 0), FActorSpawnParameters());
	map.Add(rootTile);
	
	for (int i = 1; i < mapWidth; i++) {
		FVector location;
		FRotator rotation(0,0,0);
		FActorSpawnParameters spawnInfo;

		GetSpawnPosition(map[i - 1], location);

		//Determine deltaElevation
		bool changeElevation = FMath::RandRange(1, 10) <= 2; //20% chance to change elevation
		if (changeElevation) {
			rotation = FRotator(15, 0, 0);
			currElevation += 64 * FMath::Sin(slope);
		}
		ABaseTile* newTile = GetWorld()->SpawnActor<ABaseTile>(tile, location, rotation, spawnInfo);

		map.Add(newTile);
	}
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

