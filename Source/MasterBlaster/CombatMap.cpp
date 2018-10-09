// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatMap.h"

#include "Room.h"

// Sets default values
ACombatMap::ACombatMap(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//Public Functions
void ACombatMap::AddRoom(ARoom* room) {
	map.Add(room);
}


// Called when the game starts or when spawned
void ACombatMap::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ACombatMap::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

