// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ARoom;
class ACombatMap;
class ABaseUnit;
class APlayerUnit;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
private:
	ACombatMap* map;

public:	

	UPROPERTY(EditAnywhere, Category = MapGeneration)
	int seed;

	//Special Spawn Room
	UPROPERTY(EditAnywhere, Category = MapGeneration)
	TSubclassOf<ARoom> spawnRoomBP;

	//Array of rooms the level generator can use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapGeneration)
	TArray<TSubclassOf<ARoom>> RoomLibrary;
	
	//Array of rooms the generator can use to cap off a level
	UPROPERTY(EditAnywhere, Category = MapGeneration)
	TArray<TSubclassOf<ARoom>> EndRoomLibrary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapGeneration)
	int numRooms;

	UPROPERTY(EditAnywhere, Category = Units)
	int DefaulPlayerTeamSize;

	UPROPERTY(EditAnywhere, Category = Units)
	TSubclassOf<ABaseUnit> PlayerUnitBP;

public: 	
	// Sets default values for this actor's properties
	ALevelGenerator();

private:

	void SpawnCombatMap();
	
	TArray<TSubclassOf<ARoom>> GetValidRooms(ARoom * previousRoom, TArray<TSubclassOf<ARoom>> targetLibrary);
	TSubclassOf<ARoom> SelectRoom(ARoom* previousRoom, TArray<TSubclassOf<ARoom>> targetLibrary);
	void SpawnRoom(TSubclassOf<ARoom> room, int xPosition);
	void PlaceRooms(ARoom* root);
	void SpawnPlayerTeam();
	void GenerateLevel();

	bool ValidateEditorInput();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ACombatMap* GetCombatMap();
	
};
