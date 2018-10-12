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

	UPROPERTY(EditAnywhere)
	int seed;

	//Special Spawn Room
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARoom> spawnRoomBP;

	//Array of rooms the level generator can use
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> RoomLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapGeneration)
	int numRooms;

public: 	
	// Sets default values for this actor's properties
	ALevelGenerator();

private:

	void SpawnCombatMap();
	
	TMap<int, TSubclassOf<ARoom>> GetValidRooms(ARoom * previousRoom);
	int SelectRoom(ARoom* previousRoom);
	void SpawnRoom(int roomNumber, int xPosition);
	void PlaceRooms(ARoom* root);
	void GenerateLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ACombatMap* GetCombatMap();
	
};
