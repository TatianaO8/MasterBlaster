// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ARoom;
class ACombatMap;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
private:
	ACombatMap* map;

public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	//Array of rooms the level generator can use
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ARoom>> rooms;

	UPROPERTY(EditAnywhere, Category = MapGeneration)
	int numRooms;

protected:
	int SelectRoom();
	void SpawnRoom(int roomNum, int &x);
	void GenerateLevel();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
