// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"


// Sets default values
ALevelGenerator::ALevelGenerator(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mapWidth = 100;
	ceilingHeight = 10;

	
}


//Private Functions
void ALevelGenerator::GenerateMap() {
	FVector location(0, 0, 0);
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters spawnInfo;
	
	ABaseTile* newTile = GetWorld()->SpawnActor<ABaseTile>(tile, location, rotation, spawnInfo);
	
	map.Add(newTile);
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

